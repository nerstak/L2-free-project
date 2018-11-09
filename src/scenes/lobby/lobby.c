#include "lobby.h"

extern void assets_Scene_lobby(ImageCollector* myImageCollector, bool loadOrUnload) {
    Asset* assetsList = getList_Asset("src/scenes/lobby/files.asset");

    if (loadOrUnload == true) {
        loadList_ImageCollector(myImageCollector, assetsList);
    } else {
        unloadList_ImageCollector(myImageCollector, assetsList);
    }

    clean_Asset(&assetsList);
}

extern void init_Scene_lobby(Data* data, bool loadOrUnload) {
    if (loadOrUnload == true) {
        // We init datas
    } else {
        // We free it
    }
}
