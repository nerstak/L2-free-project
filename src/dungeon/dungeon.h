#ifndef FREE_PROJECT_DUNGEONS_DUNGEON_H
#define FREE_PROJECT_DUNGEONS_DUNGEON_H

#include <stdbool.h>

#include "../utils/treemap.h"
#include "bounds.h"

typedef struct Dungeon {
    int itemCount;
    TreeMap* rooms;
    Bounds* bounds;
} Dungeon;

extern Dungeon* init_Dungeon();
extern void clean_Dungeon(Dungeon** p);
extern Bounds* getExtentBounds_Dungeon(Dungeon* p);
extern struct KeyLevelRoomMapping* getRooms_Dungeon(Dungeon* p);
extern int roomCount_Dungeon(Dungeon* p);
extern Room* getByCoord_Dungeon(Dungeon* p, Coord* c);
extern Room* getByCoordAlt_Dungeon(Dungeon* p, int x, int y);
extern void add_Dungeon(Dungeon* p, Room* r);
extern void linkOneWay_Dungeon(Dungeon* p, Room* r1, Room* r2, Symbol* c);
extern void link_Dungeon(Dungeon* p, Room* r1, Room* r2, Symbol* c);

extern bool areRoomsLinked_Dungeon(Room* r1, Room* r2);
extern Room* findStart_Dungeon(Dungeon* p);
extern Room* findBoss_Dungeon(Dungeon* p);
extern Room* findGoal_Dungeon(Dungeon* p);

#endif //FREE_PROJECT_DUNGEONS_DUNGEON_H
