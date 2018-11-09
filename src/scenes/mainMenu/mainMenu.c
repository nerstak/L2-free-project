#include "mainMenu.h"

extern void assets_Scene_mainMenu(ImageCollector* myImageCollector, bool loadOrUnload) {
    Asset* assetsList = getList_Asset("src/scenes/mainMenu/files.asset");

    if (loadOrUnload == true) {
        loadList_ImageCollector(myImageCollector, assetsList);
    } else {
        unloadList_ImageCollector(myImageCollector, assetsList);
    }

    clean_Asset(&assetsList);
}

extern void init_Scene_mainMenu(Data* data, bool loadOrUnload) {
    if (loadOrUnload == true) {
        data->mainMenu = NULL;
        data->mainMenu = malloc(1 * sizeof(mainMenu_t));

        if (data->mainMenu == NULL) {
            printf("An error occured while initializing a mainMenu_t object\n");
            exit(EXIT_FAILURE);
        }

        data->mainMenu->position = 0;
    } else {
        free(data->mainMenu);
        data->mainMenu = NULL;
    }
}
