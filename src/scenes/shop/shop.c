#include "shop.h"

extern void assets_Scene_shop(Engine* engine, Data* data, bool loadOrUnload) {
    Asset* assetsList = getList_Asset("src/scenes/shop/files.asset");

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

        data->shop->askAction = 0;
        data->shop->askTransaction = -1;
        data->shop->itemsInTransaction = 0;
        data->shop->size_shop = 0;

        data->shop->timerMessage = init_Timer();
        start_Timer(data->shop->timerMessage);
        strcpy(data->shop->messageAction, "Init");

        data->shop->shop_inv = init_ShopInventory(data->referenceItems, &(data->shop->size_shop));

        if(data->Isaac->inventory) {
            data->shop->selected = data->Isaac->inventory;
            data->shop->nSelected = 0;
        } else {
            data->shop->selected = data->shop->shop_inv;
            data->shop->nSelected = 16;
        }

    } else {
        freeAll_SlotInventory(&(data->shop->shop_inv));
        data->shop->selected = NULL;
        clean_Timer(&(data->shop->timerMessage));
        free(data->shop);
        data->shop = NULL;
    }
}
