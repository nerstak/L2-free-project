#include <stdlib.h>
#include <stdio.h>

#include "roomlist.h"

extern RoomList* init_RoomList() {
    // Initialization of a RoomList pointer
    RoomList* p = NULL;
    p = malloc(1 * sizeof(RoomList));

    // If we failed to allocate, exit the program
    if (p == NULL) {
        printf("An error occured while initializing a RoomList object");
        exit(EXIT_FAILURE);
    }

    p->next = NULL;

    return p;
}

extern KeyLevelRoomMapping* init_KeyLevelRoomMapping() {
    // Initialization of a RoomList pointer
    KeyLevelRoomMapping* p = NULL;
    p = malloc(1 * sizeof(KeyLevelRoomMapping));

    // If we failed to allocate, exit the program
    if (p == NULL) {
        printf("An error occured while initializing a KeyLevelRoomMapping object");
        exit(EXIT_FAILURE);
    }

    p->length = 3;
    p->map = malloc(p->length * sizeof(RoomList));

    for (int i = 0; i < (int) p->length; i += 1) {
        p->map[i] = NULL;
    }

    return p;
}

extern RoomList** getRooms(KeyLevelRoomMapping* p, int keylevel) {
    return &(p->map[keylevel]);
}

extern void addRoom_KeyLevelRoomMapping(KeyLevelRoomMapping* p, int keylevel, Room* r) {
    RoomList** temp = getRooms(p, keylevel);

    // Is our list of Rooms empty ?
    if ((*temp) == NULL) {
        // We write directly to the pointer
        (*temp) = malloc(1 * sizeof(RoomList));

        // If we failed to allocate, exit the program
        if ((*temp) == NULL) {
            printf("An error occured while initializing a RoomList object\n");
            exit(EXIT_FAILURE);
        }

        (*temp)->data = r;
        (*temp)->next = NULL;
    } else {
        // We find the last element of the list
        RoomList* temp2 = NULL;
        temp2 = (*temp);

        while (temp2->next != NULL) {
            temp2 = temp2->next;
        }

        // We add our element
        temp2->next = malloc(1 * sizeof(RoomList));

        // If we failed to allocate, exit the program
        if (temp2->next == NULL) {
            printf("An error occured while initializing a RoomList object\n");
            exit(EXIT_FAILURE);
        }

        temp2->next->data = r;
        temp2->next->next = NULL;
    }
}

extern RoomList* getRoom(KeyLevelRoomMapping* p, int keylevel, int i) {
    RoomList** pRoomList = getRooms(p, keylevel);
    RoomList* result = *pRoomList;

    int j = 0;
    while (j < i) {
        result = result->next;
        j += 1;
    }

    return result;
}

extern void removeRoom(KeyLevelRoomMapping* p, int keylevel, Room* r) {
    RoomList** pRoomList = getRooms(p, keylevel);
    RoomList* result = *pRoomList;

    RoomList* temp = result;
    RoomList* previous = result;

    // Is the element we want to remove the first one ?
    if (temp->data == r) {
        // We rewrite the head of our list
        p->map[keylevel] = temp->next;

        free(temp);
    } else {
        // We find the position of the element we want to remove
        while (temp != NULL && temp->data != r) {
            previous = temp;
            temp = temp->next;
        }

        if (temp == NULL) {
            return;
        }

        // Relink our list
        previous->next = temp->next;

        // Clean all the properties of our scene
        free(temp);
    }
}

extern int keyCount_KeyLevelRoomMapping(KeyLevelRoomMapping* p) {
    return (int) p->length;
}

extern int size_KeyLevelRoomMapping(KeyLevelRoomMapping* p, int keylevel) {
    RoomList** pRoomList = getRooms(p, keylevel);
    RoomList* temp = * pRoomList;

    int result = 0;
    while (temp != NULL) {
        result += 1;

        temp = temp->next;
    }

    return result;
}

extern int amountRooms_KeyLevelRoomMapping(KeyLevelRoomMapping* p, int keylevel) {
    RoomList* temp = *getRooms(p, keylevel);
    int amount = 0;

    while (temp != NULL) {
        amount += 1;

        temp = temp->next;
    }

    return amount;
}

extern void shuffleRooms_KeyLevelRoomMapping(KeyLevelRoomMapping* p, int keylevel) {
    // First we need the length of our list
    int length = amountRooms_KeyLevelRoomMapping(p, keylevel);

    RoomList** pRoomList = getRooms(p, keylevel);

    if (length == 1) {
        return;
    }

    int i = 0;
    while (i < length - 1) {
        int newPlace = (rand() % (length - (i + 1)) + (i + 1));

        if (newPlace != i) {
            if (i == 0) {
                RoomList* elA = (*pRoomList);
                RoomList* elB = getRoom(p, keylevel, newPlace);
                RoomList* prevB = getRoom(p, keylevel, newPlace - 1);

                RoomList* nextA = (*pRoomList)->next;
                RoomList* nextB = elB->next;

                (*pRoomList) = elB;
                prevB->next = elA;

                RoomList* temp = elA->next;
                elA->next = elB->next;
                elB->next = temp;
            } else {
                RoomList* elA = getRoom(p, keylevel, i);
                RoomList* elB = getRoom(p, keylevel, newPlace);
                RoomList* prevA = getRoom(p, keylevel, i - 1);
                RoomList* prevB = getRoom(p, keylevel, newPlace - 1);

                RoomList* nextA = elA->next;
                RoomList* nextB = elB->next;

                prevA->next = elB;
                prevB->next = elA;

                RoomList* temp = elA->next;
                elA->next = elB->next;
                elB->next = temp;
            }
        }

        i += 1;
    }
}

extern Room* chooseRoomWithFreeEdge(DungeonGenerator* g, KeyLevelRoomMapping* p, int keylevel) {
    shuffleRooms_KeyLevelRoomMapping(p, keylevel);
    RoomList* rooms = *getRooms(p, keylevel);
    RoomList* temp = rooms;

    for (int i = 0; i < amountRooms_KeyLevelRoomMapping(p, keylevel); i += 1) {
        Room* room = temp->data;

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

                default: {}
            }

            Coord* coord = nextInDirection_Coord(room->coord, d);

            if (getByCoord_Dungeon(g->dungeon, coord) == NULL
                && (coord->y <= 0)) { // Verify this coord->y
                return room;
            }

            clean_Direction(&d);
        }

        temp = temp->next;
    }

    return NULL;
}