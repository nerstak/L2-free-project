#include "loadingScreen.h"

extern void assets_Scene_loadingScreen(Engine* engine, Data* data, bool loadOrUnload) {
    Asset* assetsList = getList_Asset("src/scenes/loadingScreen/files.asset");

    if (loadOrUnload == true) {
        loadList_ImageCollector(engine->imageCollector, assetsList);
    } else {
        unloadList_ImageCollector(engine->imageCollector, assetsList);
    }

    clean_Asset(&assetsList);
}

extern void init_Scene_loadingScreen(Engine* engine, Data* data, bool loadOrUnload) {
    if (loadOrUnload == true) {
        // We init datas
    } else {
        // We free it
    }
}
