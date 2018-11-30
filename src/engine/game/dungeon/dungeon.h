#ifndef FREE_PROJECT_ENGINE_GAME_DUNGEON_DUNGEON_H
#define FREE_PROJECT_ENGINE_GAME_DUNGEON_DUNGEON_H

#include <stdbool.h>

#include "utils/treemap.h"
#include "bounds.h"

typedef struct Dungeon {
    int itemCount;
    TreeMap* rooms;
    Bounds* bounds;
} Dungeon;

/**
 * Create a Dungeon object
 * @return a Dungeon object
 */
extern Dungeon* init_Dungeon();
/**
 * Clean a Dungeon object
 * @param p a double pointer to a Dungeon object
 */
extern void clean_Dungeon(Dungeon** p);

/**
 * Get the Bounds of the given Dungeon
 * @param p the Dungeon object
 * @return a Bounds object
 */
extern Bounds* getExtentBounds_Dungeon(Dungeon* p);
/**
 * Get the Rooms of the given Dungeon
 * @param p the Dungeon object
 * @return a KeyLevelRoomMapping object
 */
extern struct KeyLevelRoomMapping* getRooms_Dungeon(Dungeon* p);
/**
 * Get the amount of rooms in the Dungeon
 * @param p the Dungeon object
 * @return an integer
 */
extern int roomCount_Dungeon(Dungeon* p);
/**
 * Get a Room object by its Coord
 * @param p  the Dungeon object
 * @param c  the Coord of the Room
 * @return a Room object or NULL
 */
extern Room* getByCoord_Dungeon(Dungeon* p, Coord* c);
/**
 * Get a Room object by its Coord
 * @param p  the Dungeon object
 * @param x  the x coordinate of the Room
 * @param y  the y coordinate of the Room
 * @return a Room object or NULL
 */
extern Room* getByCoordAlt_Dungeon(Dungeon* p, int x, int y);
/**
 * Add a Room object to a Dungeon object
 * @param p the Dungeon object
 * @param r the Room object
 */
extern void add_Dungeon(Dungeon* p, Room* r);
/**
 * Adds a one-way conditional (can be NULL) edge between the given rooms.
 * A one-way edge may be used to travel from r1 to r2, but not r2 to r2
 * @param p  the Dungeon object
 * @param r1 the first Room object
 * @param r2 the second Room object
 * @param c  the Condition on the Edge
 */
extern void linkOneWay_Dungeon(Dungeon* p, Room* r1, Room* r2, Symbol* c);
/**
 * Adds a two-way conditional (can be NULL) edge between the given rooms.
 * @param p  the Dungeon object
 * @param r1 the first Room object
 * @param r2 the second Room object
 * @param c  the Condition on the Edge
 */
extern void link_Dungeon(Dungeon* p, Room* r1, Room* r2, Symbol* c);

/**
 * Verify that 2 rooms are linked
 * @param r1 the first Room object
 * @param r2 the second Room object
 * @return a boolean according to the result
 */
extern bool areRoomsLinked_Dungeon(Room* r1, Room* r2);
/**
 * Get the Start Room of a given Dungeon object
 * @param p the Dungeon object
 * @return a Room object or NULL
 */
extern Room* findStart_Dungeon(Dungeon* p);
/**
 * Get the Boss Room of a given Dungeon object
 * @param p the Dungeon object
 * @return a Room object or NULL
 */
extern Room* findBoss_Dungeon(Dungeon* p);
/**
 * Get the Goal Room of a given Dungeon object
 * @param p the Dungeon object
 * @return a Room object or NULL
 */
extern Room* findGoal_Dungeon(Dungeon* p);

#endif //FREE_PROJECT_ENGINE_GAME_DUNGEON_DUNGEON_H
