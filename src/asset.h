#ifndef FREE_PROJECT_ASSET_H
#define FREE_PROJECT_ASSET_H

typedef struct Asset {
    char name[255];
    char path[255];
    int type;

    struct Asset* next;
} Asset;

extern Asset* getList_Asset(char path[]);
extern void clean_Asset(Asset** assetList);

#endif //FREE_PROJECT_ASSET_H
