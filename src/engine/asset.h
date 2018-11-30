#ifndef FREE_PROJECT_ENGINE_ASSET_H
#define FREE_PROJECT_ENGINE_ASSET_H

typedef struct Asset {
    char name[255];
    char path[255];
    int type;

    struct Asset* next;
} Asset;

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

#endif //FREE_PROJECT_ENGINE_ASSET_H
