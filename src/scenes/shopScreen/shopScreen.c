#include "shopScreen.h"

extern void assets_Scene_shop(ImageCollector* myImageCollector, bool loadOrUnload) {
    Asset* assetsList = getList_Asset("src/scenes/shopScreen/files.asset");

    if (loadOrUnload == true) {
        loadList_ImageCollector(myImageCollector, assetsList);
    } else {
        unloadList_ImageCollector(myImageCollector, assetsList);
    }

    clean_Asset(&assetsList);
}

extern void init_Scene_shop(Data* data, bool loadOrUnload) {
    if (loadOrUnload == true) {
        data->shop = NULL;
        data->shop = malloc(1 * sizeof(shop_t));

        if (data->shop == NULL) {
            printf("An error occured while initializing a shop_t object\n");
            exit(EXIT_FAILURE);
        }

        data->shop->n_selected = 0;
        data->shop->ask_action = 0;

        data->shop->shop_inv = init_shop();
        data->shop->selected = data->shop->shop_inv;
    } else {
        slot_inventory * current;
        do{
            current = data->shop->shop_inv;
            if(current->next == NULL) {
                free_item(current);
                current = NULL;
            } else {
                current = current->next;
                free_item(current->prev);
            }
        }while(current != NULL);
        data->shop->selected = NULL;
        free(data->shop);
        data->shop = NULL;
    }
}
