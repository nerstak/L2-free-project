#ifndef FREE_PROJECT_GENERATOR_H
#define FREE_PROJECT_GENERATOR_H

#include "dungeon.h"
#include "stdlib.h"

typedef struct DungeonGenerator {
    int seed;
    Dungeon* dungeon;
} DungeonGenerator;

typedef struct KeyLevelRoomMapping {
    struct RoomList** map;
    size_t length;
} KeyLevelRoomMapping;

extern DungeonGenerator* init_DungeonGenerator(int seed);
extern void clean_DungeonGenerator(DungeonGenerator** p);

extern void generate_DungeonGenerator(DungeonGenerator* p);

#endif //FREE_PROJECT_GENERATOR_H
