#include "loadingScreen.h"

extern void assets_Scene_loadingScreen(Engine* engine, Data* data, bool loadOrUnload) {
    char path[] = "src/scenes/loadingScreen/files.asset";
    load_Asset(path, loadOrUnload, engine, data);
}

extern void init_Scene_loadingScreen(Engine* engine, Data* data, bool loadOrUnload) {
    if (loadOrUnload == true) {
        // We init data
    } else {
        // We free it
    }
}
