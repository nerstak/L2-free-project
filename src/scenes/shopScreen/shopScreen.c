#include "shopScreen.h"

extern void assets_Scene_shop(Engine* engine, Data* data, bool loadOrUnload) {
    Asset* assetsList = getList_Asset("src/scenes/shopScreen/files.asset");

    if (loadOrUnload == true) {
        loadList_ImageCollector(engine->imageCollector, assetsList);
    } else {
        unloadList_ImageCollector(engine->imageCollector, assetsList);
    }

    clean_Asset(&assetsList);
}

extern void init_Scene_shop(Engine* engine, Data* data, bool loadOrUnload) {
    if (loadOrUnload == true) {
        data->shop = NULL;
        data->shop = malloc(1 * sizeof(shop_t));

        if (data->shop == NULL) {
            printf("An error occured while initializing a shop_t object\n");
            exit(EXIT_FAILURE);
        }

        data->Isaac = malloc(sizeof(Player));
        data->Isaac->size_inventory = 0;
        data->Isaac->inventory = NULL;
        data->Isaac->money = 500;

        data->shop->n_selected = 0;
        data->shop->ask_action = 0;

        data->shop->shop_inv = init_SlotInventory();
        data->shop->selected = data->shop->shop_inv;
    } else {
        SlotInventory * current;
        do{
            current = data->shop->shop_inv;
            if(current->next == NULL) {
                freeOne_SlotInventory(current);
                current = NULL;
            } else {
                current = current->next;
                freeOne_SlotInventory(current->prev);
            }
        }while(current != NULL);
        data->shop->selected = NULL;
        free(data->shop);
        data->shop = NULL;
    }
}
