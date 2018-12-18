#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>

#include "../../../utils/math.h"

#include "generator.h"
#include "roomlist.h"

// Global var used to be able to throw from a sub function
jmp_buf ex_buf__;
#define TRY do { if( !setjmp(ex_buf__) ) {
#define CATCH } else {
#define ETRY } } while(0)
#define THROW longjmp(ex_buf__, 1)

static int MAX_RETRIES = 20;

static double INTENSITY_GROWTH_JITTER = 0.1;
static double INTENSITY_EASE_OFF = 0.2;

static int maxSpaces = 20;
static int maxKeys = 5; // Whatever no time to redo the algo again it works.

static Direction* chooseFreeEdge(DungeonGenerator* g, Room* room);

static double applyIntensity(Room* room, double intensity);
static void normalizeIntensity(DungeonGenerator* p);

static void initEntranceRoom_DungeonGenerator(DungeonGenerator* p, KeyLevelRoomMapping* levels);
static void placeRooms_DungeonGenerator(DungeonGenerator* p, KeyLevelRoomMapping* levels);
static void placeBossGoalRooms_DungeonGenerator(DungeonGenerator* p, KeyLevelRoomMapping* levels);
static void graphify_DungeonGenerator(DungeonGenerator* p, KeyLevelRoomMapping* levels);
static void computeIntensity_DungeonGenerator(DungeonGenerator* p, KeyLevelRoomMapping* levels);
static void placeKeys_DungeonGenerator(DungeonGenerator* p, KeyLevelRoomMapping* levels);

extern DungeonGenerator* init_DungeonGenerator(int seed) {
    // Initialization of a DungeonGenerator pointer
    DungeonGenerator* p = NULL;
    p = malloc(1 * sizeof(DungeonGenerator));

    // If we failed to allocate, exit the program
    if (p == NULL) {
        printf("An error occured while initializing a DungeonGenerator object");
        exit(EXIT_FAILURE);
    }

    p->seed = seed;
    p->dungeon = NULL;

    srand((unsigned) p->seed);

    return p;
}

extern void clean_DungeonGenerator(DungeonGenerator** p) {
    if ((*p) != NULL) {
        // First we free the memory
        free(*(p));
        // We set the pointer to NULL by security
        *(p) = NULL;
    }
}

static Direction* chooseFreeEdge(DungeonGenerator* g, Room* room) {
    int d0 = rand() % 4;

    for (int i = 0; i < 4; i += 1) {
        Direction* d = fromCode_Direction((d0 + i) % 4);
        Coord* coord = nextInDirection_Coord(room->coord, d);

        if (getByCoord_Dungeon(g->dungeon, coord) == NULL && coord->y <= 0) { // Verify this coord->y <= 0
            clean_Coord(&coord);

            return d;
        }

        clean_Direction(&d);
        clean_Coord(&coord);
    }

    // Asert false
    return NULL;
}

static double applyIntensity(Room* room, double intensity) {
    intensity *= 1.0 - INTENSITY_GROWTH_JITTER/2.0 + INTENSITY_GROWTH_JITTER * ((double) rand() / RAND_MAX);

    setDifficulty_Room(room, intensity);

    double maxIntensity = intensity;
    Room** children = getChildren_Room(room);

    for (int i = 0; (size_t) i < room->childrenLength; i += 1) {
        if (impliesCondition_Condition(getPrecondition_Room(room), getPrecondition_Room(children[i]))) {
            maxIntensity = maxDouble(maxIntensity, applyIntensity(children[i], intensity + 1.0));
        }
    }

    return maxIntensity;
}

static void normalizeIntensity(DungeonGenerator* p) {
    double maxIntensity = 0.0;
    KeyLevelRoomMapping* keylevel = getRooms_Dungeon(p->dungeon);
    RoomList* rooms = keylevel->map[0];
    RoomList* temp = rooms;

    while (temp != NULL) {
        maxIntensity = maxDouble(maxIntensity, getDifficulty_Room(temp->data));

        temp = temp->next;
    }

    temp = rooms;
    while (temp != NULL) {
        setDifficulty_Room(temp->data, getDifficulty_Room(temp->data) * 0.99 / maxIntensity);

        temp = temp->next;
    }

    clean_KeyLevelRoomMapping(&(keylevel));
}

extern void generate_DungeonGenerator(DungeonGenerator* p) {
    int attempt = 0;

    while (true) {
        KeyLevelRoomMapping* levelsCatch = NULL;

        TRY {
            p->dungeon = init_Dungeon();

            // Maps of keylevel -> A list of rooms created with a specific lockCount
            KeyLevelRoomMapping* levels = init_KeyLevelRoomMapping(maxKeys);
            levelsCatch = levels;

            // Create the entrance to our dungeon
            initEntranceRoom_DungeonGenerator(p, levels);

            // Fill the dungeon
            placeRooms_DungeonGenerator(p, levels);

            // Place a Boss and Goal rooms in the dungeon
            placeBossGoalRooms_DungeonGenerator(p, levels);

            // Make it more like a graph
            graphify_DungeonGenerator(p, levels);

            // Compute intensities
            computeIntensity_DungeonGenerator(p, levels);

            // Place keys
            placeKeys_DungeonGenerator(p, levels);

            clean_KeyLevelRoomMapping(&levels);

            return;
        } CATCH {
            if (++attempt > MAX_RETRIES) {
                // Dungeon generation failed.

                clean_KeyLevelRoomMapping(&levelsCatch);
                clean_Dungeon(&(p->dungeon));

                return;
            }

            // Retrying
            clean_KeyLevelRoomMapping(&levelsCatch);
            clean_Dungeon(&(p->dungeon));
        } ETRY;
    }
}

static void initEntranceRoom_DungeonGenerator(DungeonGenerator* p, KeyLevelRoomMapping* levels) {
    Coord* coord = init_Coord(0, 0);
    Room* room = init_Room(coord, NULL, init_Symbol(START), initTrue_Condition());

    add_Dungeon(p->dungeon, room);
    addRoom_KeyLevelRoomMapping(levels, 0, room);
}

static void placeRooms_DungeonGenerator(DungeonGenerator* p, KeyLevelRoomMapping* levels) {
    int roomsPerLock = maxSpaces / maxKeys; // A lock is a "region" locked by a Condition, a key here

    int keylevel = 0;
    Symbol* latestKey = NULL;
    Condition* condition = initTrue_Condition();

    while (roomCount_Dungeon(p->dungeon) < maxSpaces) {
        bool doLock = false;

        if (amountRooms_KeyLevelRoomMapping(levels, keylevel) >= roomsPerLock
            && keylevel < maxKeys) {
            latestKey = init_Symbol(keylevel++); // https://stackoverflow.com/questions/12988140/what-is-the-difference-between-and-1-operators
            condition = initAndSymbol_Condition(condition, latestKey);
            doLock = true;
        }

        Room* parentRoom = NULL;
        if (!doLock && ((rand() % 10) > 0)) {
            parentRoom = chooseRoomWithFreeEdge(p, levels, keylevel);
        }
        if (parentRoom == NULL) {
            KeyLevelRoomMapping* rooms = getRooms_Dungeon(p->dungeon);
            parentRoom = chooseRoomWithFreeEdge(p, rooms, 0);
            clean_KeyLevelRoomMapping(&rooms);
            doLock = true;
        }

        Direction* d = chooseFreeEdge(p, parentRoom);
        Coord* coords = nextInDirection_Coord(parentRoom->coord, d);
        Room* room = init_Room(coords, parentRoom, NULL, initCopy_Condition(condition));

        if (get_TreeMap(p->dungeon->rooms, room->coord) != NULL) {
            THROW;
        }

        add_Dungeon(p->dungeon, room);
        addChild_Room(parentRoom, room);
        link_Dungeon(p->dungeon, parentRoom, room, doLock ? latestKey : NULL);

        addRoom_KeyLevelRoomMapping(levels, keylevel, room);

        clean_Direction(&d);
    }
}

static void placeBossGoalRooms_DungeonGenerator(DungeonGenerator* p, KeyLevelRoomMapping* levels) {
    KeyLevelRoomMapping* possibleGoalRooms = init_KeyLevelRoomMapping(1);
    possibleGoalRooms->length = 1;
    KeyLevelRoomMapping* rooms = getRooms_Dungeon(p->dungeon);
    RoomList* temp = *getRooms_KeyLevelRoomMapping(rooms, 0);

    while (temp != NULL) {
        if (temp->data->childrenLength > 0 ||
            getItem_Room(temp->data) != NULL) {

            temp = temp->next;
        } else {
            Room* parent = getParent_Room(temp->data);

            if (parent == NULL || parent->childrenLength != 1 ||
                getItem_Room(temp->data) != NULL ||
                !impliesCondition_Condition(getPrecondition_Room(parent), getPrecondition_Room(temp->data))) {

                temp = temp->next;
            } else {
                addRoom_KeyLevelRoomMapping(possibleGoalRooms, 0, temp->data);
                temp = temp->next;
            }
        }
    }

    if (amountRooms_KeyLevelRoomMapping(possibleGoalRooms, 0) == 0) {
        clean_KeyLevelRoomMapping(&possibleGoalRooms);
        clean_KeyLevelRoomMapping(&rooms);

        THROW;
    }

    int length = amountRooms_KeyLevelRoomMapping(possibleGoalRooms, 0);

    Room* goalRoom = getRoom_KeyLevelRoomMapping(possibleGoalRooms, 0, rand() % length)->data;
    Room* bossRoom = getParent_Room(goalRoom);

    setItem_Room(goalRoom, init_Symbol(GOAL));
    setItem_Room(bossRoom, init_Symbol(BOSS));

    clean_KeyLevelRoomMapping(&(possibleGoalRooms));
    clean_KeyLevelRoomMapping(&rooms);
}

static void graphify_DungeonGenerator(DungeonGenerator* p, KeyLevelRoomMapping* levels) {
    KeyLevelRoomMapping* rooms = getRooms_Dungeon(p->dungeon);
    RoomList* temp = *getRooms_KeyLevelRoomMapping(rooms, 0);

    while (temp != NULL) {
        if (isGoal_Room(temp->data) || isBoss_Room(temp->data)) {
            temp = temp->next;
        } else {
            for (int j = 0; j < 4; j += 1) {
                Direction* d = NULL;

                switch (j) {
                    case 0: {
                        d = init_Direction(j, 0, -1);

                        break;
                    }

                    case 1: {
                        d = init_Direction(j, 1, 0);

                        break;
                    }

                    case 2: {
                        d = init_Direction(j, 0, 1);

                        break;
                    }

                    case 3: {
                        d = init_Direction(j, -1, 0);

                        break;
                    }

                    default: {
                    }
                }

                if (getEdge_Room(temp->data, d) != NULL) {
                    //temp = temp->next;
                } else {
                    Room* nextRoom = getByCoord_Dungeon(p->dungeon, nextInDirection_Coord(temp->data->coord, d));

                    if (nextRoom == NULL || isGoal_Room(nextRoom) || isBoss_Room(nextRoom)) {
                        //temp = temp->next;
                    } else {
                        bool forwardImplies = impliesCondition_Condition(getPrecondition_Room(temp->data), getPrecondition_Room(nextRoom));
                        bool backwardImplies = impliesCondition_Condition(getPrecondition_Room(nextRoom), getPrecondition_Room(temp->data));

                        if (forwardImplies && backwardImplies) {
                            // Same keylevel
                            if (rand() % 5 != 0) {
                                temp = temp->next;
                            } else {
                                link_Dungeon(p->dungeon, temp->data, nextRoom, NULL);
                            }
                        } else {
                            Symbol* difference = singleSymbolDifference_Condition(getPrecondition_Room(temp->data), getPrecondition_Room(nextRoom));

                            if (difference == NULL) {
                                //temp = temp->next; // Verify condition here
                            } else {
                                link_Dungeon(p->dungeon, temp->data, nextRoom, difference);
                            }
                        }
                    }
                }

                clean_Direction(&(d));
            }

            temp = temp->next;
        }
    }

    clean_KeyLevelRoomMapping(&(rooms));
}

static void computeIntensity_DungeonGenerator(DungeonGenerator* p, KeyLevelRoomMapping* levels) {
    double nextLevelBaseIntensity = 0.0;
    for (int level = 0; level < keyCount_KeyLevelRoomMapping(levels); level += 1) {
        double intensity = nextLevelBaseIntensity * (1.0 - INTENSITY_EASE_OFF);

        RoomList* temp = *getRooms_KeyLevelRoomMapping(levels, level);

        while (temp != NULL) {
            if (getParent_Room(temp->data) == NULL ||
                !impliesCondition_Condition(getPrecondition_Room(getParent_Room(temp->data)), getPrecondition_Room(temp->data))) {
                nextLevelBaseIntensity = maxDouble(nextLevelBaseIntensity, applyIntensity(temp->data, intensity));
            }

            temp = temp->next;
        }
    }

    normalizeIntensity(p);

    setDifficulty_Room(findBoss_Dungeon(p->dungeon), 1.0);
    setDifficulty_Room(findGoal_Dungeon(p->dungeon), 0.0);
}

static void placeKeys_DungeonGenerator(DungeonGenerator* p, KeyLevelRoomMapping* levels) {
    for (int level = 0; level < keyCount_KeyLevelRoomMapping(levels); level += 1) {
        shuffleRooms_KeyLevelRoomMapping(levels, level);
        sortRooms_KeyLevelRoomMapping(levels, level);

        bool placedKey = false;

        RoomList* temp = *getRooms_KeyLevelRoomMapping(levels, level);

        while (temp != NULL) {
            if (getItem_Room(temp->data) == NULL) {
                setItem_Room(temp->data, init_Symbol(level));
                placedKey = true;
                break;
            }

            temp = temp->next;
        }

        if (placedKey == false) {
            THROW;
        }
    }
}