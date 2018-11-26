#include "inventoryScreen.h"

extern void assets_Scene_inventory(Engine* engine, Data* data, bool loadOrUnload) {
    Asset* assetsList = getList_Asset("src/scenes/inventoryScreen/files.asset");

    if (loadOrUnload == true) {
        loadList_ImageCollector(engine->imageCollector, assetsList);
    } else {
        unloadList_ImageCollector(engine->imageCollector, assetsList);
    }

    clean_Asset(&assetsList);
}

extern void init_Scene_inventory(Engine* engine, Data* data, bool loadOrUnload) {
    if (loadOrUnload == true) {
        data->inventory = NULL;
        data->inventory = malloc(sizeof(inventory_t));

        if(data->inventory == NULL) {
            printf("An error occured while initializing a inventory_t object\n");
            exit(EXIT_FAILURE);
        }

        data->inventory->nSelected = 0;
        data->inventory->askAction = 0;
        data->inventory->askDeletion = -1;
        data->inventory->timerMessage = init_Timer();

        data->inventory->selected = data->Isaac->inventory;
    } else {
        data->inventory->selected = NULL;
        free(data->inventory);
        data->inventory = NULL;
        clean_Timer(&(data->inventory->timerMessage));
    }
}
