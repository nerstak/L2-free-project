#ifndef FREE_PROJECT_UTILS_TREEMAP_H
#define FREE_PROJECT_UTILS_TREEMAP_H

#include "coord.h"
#include "../dungeon/room.h"

typedef struct TreeMapNode {
    Coord* key;
    Room* value;

    bool red;

    struct TreeMapNode* link[2];
} TreeMapNode;

typedef struct TreeMap {
    TreeMapNode* root;
} TreeMap;

extern TreeMap* init_TreeMap();
extern void clean_TreeMap(TreeMap** tree);
extern void printf_TreeMap(TreeMap* tree);

extern TreeMapNode* get_TreeMap(TreeMap* tree, Coord* myCoord);
extern void put_TreeMap(TreeMap* tree, Room* myRoom);
extern void delete_TreeMap(TreeMap* tree, Room* value);

extern int size_TreeMap(TreeMapNode* tree);

#endif //FREE_PROJECT_UTILS_TREEMAP_H
