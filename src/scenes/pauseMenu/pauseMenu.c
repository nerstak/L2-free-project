#include <time.h>
#include "pauseMenu.h"

extern void assets_Scene_pauseMenu(Engine* engine, Data* data, bool loadOrUnload) {
    Asset* assetsList = getList_Asset("src/scenes/pauseMenu/files.asset");

    if (loadOrUnload == true) {
        loadList_ImageCollector(engine->imageCollector, assetsList);
    } else {
        unloadList_ImageCollector(engine->imageCollector, assetsList);
    }

    clean_Asset(&assetsList);
}

extern void init_Scene_pauseMenu(Engine* engine, Data* data, bool loadOrUnload) {
    if (loadOrUnload == true) {
        data->pauseMenu = NULL;
        data->pauseMenu = malloc(sizeof(pauseMenu_t));

        if(!data->pauseMenu) {
            printf("An error occured while initializing a pauseMenu_t object\n");
            exit(EXIT_FAILURE);
        }

        data->pauseMenu->backGame = 0;
        data->pauseMenu->askAction = 0;
        data->pauseMenu->position = 0;
    } else {
        free(data->pauseMenu);
        data->pauseMenu = NULL;
    }
}
