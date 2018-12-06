#ifndef FREE_PROJECT_ENGINE_ASSET_H
#define FREE_PROJECT_ENGINE_ASSET_H

#include <stdbool.h>

typedef struct Asset {
    char name[255];
    char path[255];
    int type;

    struct Asset* next;
} Asset;

struct Engine;
struct Data;

/**
 * Create a Asset SLL of a given file of assets
 * @param path a string to the file of assets
 * @return a Asset SLL object
 */
extern Asset* getList_Asset(char path[]);
/**
 * Clean a Asset SLL object
 * @param assetList a double pointer to a Asset SLL
 */
extern void clean_Asset(Asset** assetList);

/**
 * Load or unload the asset of a given path
 * @param path a path to a .assets file
 * @param loadOrUnload a boolean (load or unload)
 * @param engine an Engine object
 * @param data a Data object
 */
extern void load_Asset(char path[], bool loadOrUnload, struct Engine* engine, struct Data* data);

#endif //FREE_PROJECT_ENGINE_ASSET_H
