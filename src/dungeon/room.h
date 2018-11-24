#ifndef FREE_PROJECT_DUNGEONS_ROOM_H
#define FREE_PROJECT_DUNGEONS_ROOM_H

#include <stdlib.h>

#include "condition.h"
#include "../utils/coord.h"
#include "edge.h"

typedef struct Room {
    Condition* preCondition;
    Coord* coord;
    Symbol* item;
    Edge* edges[4];
    double difficulty;
    size_t childrenLength;
    struct Room* parent;
    struct Room* children[];
} Room;

/**
 * Create a Room object with given Coord object, Room object, Symbol object, Condition object
 * @param coord        the Coord
 * @param parent       the parent Room
 * @param item         the Symbol
 * @param preCondition the pre Condition
 * @return a Room object
 */
extern Room* init_Room(Coord* coord, Room* parent, Symbol* item, Condition* preCondition);
/**
 * Clean a Room object
 * @param myRoom a double pointer to a Coord object
 */
extern void clean_Room(Room** myRoom);
/**
 * Get the difficulty of a given Room
 * @param myRoom the Room object
 * @return a double representing the Room's difficulty
 */
extern double getDifficulty_Room(Room* myRoom);
/**
 * Set the difficulty of a given Room
 * @param myRoom     the Room object
 * @param difficulty the difficulty, a double
 */
extern void setDifficulty_Room(Room* myRoom, double difficulty);
/**
 * Get the Symbol of a given Room
 * @param myRoom the Room object
 * @return a Symbol object
 */
extern Symbol* getItem_Room(Room* myRoom);
/**
 * Set the Symbol of a given Room
 * @param myRoom the Room object
 * @param item   the Symbol object
 */
extern void setItem_Room(Room* myRoom, Symbol* item);
/**
 * Get the Edges (an array) of a given Room
 * @param myRoom the Room object
 * @return the array of Edges object
 */
extern Edge** getEdges_Room(Room* myRoom);
/**
 * Get the Edge of a given Room in a given Direction
 * @param myRoom    the Room object
 * @param direction the Direction object
 * @return a Edge object or NULL
 */
extern Edge* getEdge_Room(Room* myRoom, Direction* direction);
/**
 * Give the amount of Edge of a given Room
 * @param myRoom the Room object
 * @return the amount of Edge, an integer
 */
extern int linkAmount_Room(Room* myRoom);

/**
 * Verify if a given Room is the Start Room
 * @param myRoom the Room object
 * @return a boolean according to the result
 */
extern bool isStart_Room(Room* myRoom);
/**
 * Verify if a given Room is the Goal Room
 * @param myRoom the Room object
 * @return a boolean according to the result
 */
extern bool isGoal_Room(Room* myRoom);
/**
 * Verify if a given Room is the Boss Room
 * @param myRoom the Room object
 * @return a boolean according to the result
 */
extern bool isBoss_Room(Room* myRoom);

/**
 * Get the pre Condition of a given Room
 * @param myRoom the Room object
 * @return a Condition object or NULL
 */
extern Condition* getPrecondition_Room(Room* myRoom);
/**
 * Set the pre Condition of a given Room
 * @param myRoom       the Room object
 * @param preCondition the Condition object
 */
extern void setPrecondition_Room(Room* myRoom, Condition* preCondition);

/**
 * Get the parent Room of a given Room
 * @param myRoom the Room object
 * @return a Room object
 */
extern Room* getParent_Room(Room* myRoom);
/**
 * Set the parent Room of a given Room
 * @param myRoom the Room object
 * @param parent the parent Room object
 */
extern void setParent_Room(Room* myRoom, Room* parent);
/**
 * Get the Array of Children Rooms
 * @param myRoom the Room object
 * @return an array of Room object
 */
extern Room** getChildren_Room(Room* myRoom);
/**
 * Add a child Room to a given Room
 * @param myRoom the Room object
 * @param child  the child Room object
 */
extern void addChild_Room(Room* myRoom, Room* child);

/**
 * Print a given Room (test purpose)
 * @param myRoom the Room object
 */
extern void printf_Room(Room* myRoom);

#endif //FREE_PROJECT_DUNGEONS_ROOM_H
