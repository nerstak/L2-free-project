#include "dungeon.h"

extern void assets_Scene_Dungeon(Engine* engine, Data* data, bool loadOrUnload) {
    Asset* assetsList = getList_Asset("src/scenes/dungeon/files.asset");

    if (loadOrUnload == true) {
        data->Isaac->current_stats->health -= 4;
        loadList_ImageCollector(engine->imageCollector, assetsList);
    } else {
        unloadList_ImageCollector(engine->imageCollector, assetsList);
    }

    clean_Asset(&assetsList);
}

extern void init_Scene_Dungeon(Engine* engine, Data* data, bool loadOrUnload) {
    if (loadOrUnload == true) {

    } else {

    }
}