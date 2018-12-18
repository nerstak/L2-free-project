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

/**
 * Create a DungeonGenerator object
 * @param seed a integer for the random seed
 * @return a DungeonGenerator object
 */
extern DungeonGenerator* init_DungeonGenerator(int seed);
/**
 * Clean a DungeonGenerator object
 * @param p a double pointer to a DungeonGenerator object
 */
extern void clean_DungeonGenerator(DungeonGenerator** p);

/**
 * Generate a dungeon
 * @param p a DungeonGenerator object
 */
extern void generate_DungeonGenerator(DungeonGenerator* p);

#endif //FREE_PROJECT_GENERATOR_H
