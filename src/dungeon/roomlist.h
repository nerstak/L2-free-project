#ifndef FREE_PROJECT_DUNGEON_ROOMLIST_H
#define FREE_PROJECT_DUNGEON_ROOMLIST_H

#include "room.h"
#include "generator.h"

typedef struct RoomList {
    Room* data;
    struct RoomList* next;
} RoomList;

extern RoomList* init_RoomList();
extern KeyLevelRoomMapping* init_KeyLevelRoomMapping();

extern RoomList** getRooms(KeyLevelRoomMapping* p, int keylevel);
extern void addRoom_KeyLevelRoomMapping(KeyLevelRoomMapping* p, int keylevel, Room* r);
extern RoomList* getRoom(KeyLevelRoomMapping* p, int keylevel, int i);
extern void removeRoom(KeyLevelRoomMapping* p, int keylevel, Room* r);
extern int keyCount_KeyLevelRoomMapping(KeyLevelRoomMapping* p);
/**
extern int amountRooms_KeyLevelRoomMapping(KeyLevelRoomMapping* p, int keylevel);
extern void shuffleRooms_KeyLevelRoomMapping(KeyLevelRoomMapping* p, int keylevel);
extern Room* chooseRoomWithFreeEdge(DungeonGenerator* g, KeyLevelRoomMapping* p, int keylevel);

#endif //FREE_PROJECT_DUNGEON_ROOMLIST_H
