#ifndef FREE_PROJECT_DUNGEON_ROOMLIST_H
#define FREE_PROJECT_DUNGEON_ROOMLIST_H

#include "room.h"
#include "generator.h"

typedef struct RoomList {
    Room* data;
    struct RoomList* next;
} RoomList;

/**
 * Create a RoomList object
 * @return a RoomList object
 */
extern RoomList* init_RoomList();
/**
 * Create a KeyLevelRoomMapping object
 * @return a KeyLevelRoomMapping object
 */
extern KeyLevelRoomMapping* init_KeyLevelRoomMapping();

// TODO: clean functions

/**
 * Get a double pointer on the beginning of a RoomList object (SLL)
 * @param p        a KeyLevelRoomMapping object
 * @param keylevel a keylevel, an integer
 * @return a double pointer on a RoomList object
 */
extern RoomList** getRooms(KeyLevelRoomMapping* p, int keylevel);
/**
 * Add a Room to a given KeyLevelRoomMapping at a given keylevel
 * @param p        a KeyLevelRoomMapping object
 * @param keylevel a keylevel, an integer
 * @param r        a Room object
 */
extern void addRoom_KeyLevelRoomMapping(KeyLevelRoomMapping* p, int keylevel, Room* r);
/**
 * Get the n-th Room of a given KeyLevelRoomMapping at a given keylevel
 * @param p        a KeyLevelRoomMapping object
 * @param keylevel a keylevel, an integer
 * @param i        an index, an integer
 * @return a RoomList object
 */
extern RoomList* getRoom(KeyLevelRoomMapping* p, int keylevel, int i);
/**
 * Remove a given Room of a given KeyLevelRoomMapping at a given keylevel
 * @param p        a KeyLevelRoomMapping object
 * @param keylevel a keylevel, an integer
 * @param r        a Room object
 */
extern void removeRoom(KeyLevelRoomMapping* p, int keylevel, Room* r);
/**
 * Get the amount of "keylevel" of a given KeyLevelRoomMapping
 * @param p a KeyLevelRoomMapping object
 * @return the amount of keylevel, an integer
 */
extern int keyCount_KeyLevelRoomMapping(KeyLevelRoomMapping* p);
/**
 * Get the amount of Room of a given KeyLevelRoomMapping at a given keylevel
 * @param p        a KeyLevelRoomMapping object
 * @param keylevel a keylevel, an integer
 * @return the amount of Room, an integer
 */
extern int amountRooms_KeyLevelRoomMapping(KeyLevelRoomMapping* p, int keylevel);
/**
 * Shuffle the RoomList of a given KeyLevelRoomMapping at a given keylevel
 * @param p        a KeyLevelRoomMapping object
 * @param keylevel a keylevel, an integer
 */
extern void shuffleRooms_KeyLevelRoomMapping(KeyLevelRoomMapping* p, int keylevel);
/**
 * Choose a random Room with free Edge
 * @param g        a DungeonGenerator object
 * @param p        a KeyLevelRoomMapping object
 * @param keylevel a keylevel, an integer
 * @return a Room object
 */
extern Room* chooseRoomWithFreeEdge(DungeonGenerator* g, KeyLevelRoomMapping* p, int keylevel);

#endif //FREE_PROJECT_DUNGEON_ROOMLIST_H
