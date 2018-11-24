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

/**
 * Create a TreeMap object (RB Tree)
 * @return a TreeMap object
 */
extern TreeMap* init_TreeMap();
/**
 * Clean a TreeMap object
 * @param tree a double pointer to a TreeMap object
 */
extern void clean_TreeMap(TreeMap** tree);
/**
 * Print a Tree (test purpose)
 * @param tree the TreeMap to display
 */
extern void printf_TreeMap(TreeMap* tree);

/**
 * Get a TreeMapNode by his Coord
 * @param tree    the source TreeMap from which we get/search the TreeMapNode
 * @param myCoord the Coord query
 * @return a TreeMapNode object according to the Coord object given or NULL
 */
extern TreeMapNode* get_TreeMap(TreeMap* tree, Coord* myCoord);
/**
 * Add a Room to the TreeMap
 * @param tree   the TreeMap to update
 * @param myRoom the Room to add
 */
extern void put_TreeMap(TreeMap* tree, Room* myRoom);
/**
 * Delete a given Room from the TreeMap
 * @param tree  the TreeMap to update
 * @param value the Room to remove
 */
extern void delete_TreeMap(TreeMap* tree, Room* value);

/**
 * Get the size (the amount of TreeMapNode) of a given TreeMap
 * @param tree the TreeMap to measure
 * @return the size of the given TreeMap
 */
extern int size_TreeMap(TreeMapNode* tree);

#endif //FREE_PROJECT_UTILS_TREEMAP_H
