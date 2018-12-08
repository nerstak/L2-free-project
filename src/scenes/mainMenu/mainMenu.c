#include "mainMenu.h"

extern void assets_Scene_mainMenu(Engine* engine, Data* data, bool loadOrUnload) {
    Asset* assetsList = getList_Asset("src/scenes/mainMenu/files.asset");

    if (loadOrUnload == true) {
        loadList_ImageCollector(engine->imageCollector, assetsList);
    } else {
        unloadList_ImageCollector(engine->imageCollector, assetsList);
    }

    clean_Asset(&assetsList);
}

extern void init_Scene_mainMenu(Engine* engine, Data* data, bool loadOrUnload) {
    if (loadOrUnload == true) {
        data->mainMenu = NULL;
        data->mainMenu = malloc(1 * sizeof(mainMenu_t));

        if (data->mainMenu == NULL) {
            printf("An error occured while initializing a mainMenu_t object\n");
            exit(EXIT_FAILURE);
        }

        data->mainMenu->position = 0;
        data->mainMenu->askAction = 0;

        if(data->Isaac) {
            free_Player(&(data->Isaac));
        }
        if(data->field) {
            freeField(&(data->field));
        }
        if(data->referenceItems) {
            freeReference(&(data->referenceItems));
        }



    } else {
        free(data->mainMenu);
        data->mainMenu = NULL;
    }
}
