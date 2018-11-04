#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "shopScreen.h"

#include "../inventory.h"
#include "../image.h"
#include "../window.h"
#include "../data.h"
#include "../player.h"

static SDL_Surface* getShop(ImageCollector* myImageCollector, FontCollector* myFontCollector, Data* data);

static void moveShopSelector(Data * data,slot_inventory * shop_list, slot_inventory * player_list);
static void buy_item(Data * data, slot_inventory * item_buying);
static void sell_item(Data * data, slot_inventory * item_selling);

extern void assets_Scene_shop(ImageCollector* myImageCollector, bool loadOrUnload) {
    Asset* assetsList = getList_Asset("src/scenes/shopScreen.asset");

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

extern void eventProcess_Scene_shop(SDL_Event event, Data* data) {
    switch (event.type) {
        case SDL_KEYDOWN: {
            // Key pressed
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    data->shop->ask_action = -10;
                    break;
                case SDLK_DOWN:
                    data->shop->ask_action = 10;
                    break;
                case SDLK_LEFT:
                    data->shop->ask_action = -1;
                    break;
                case SDLK_RIGHT:
                    data->shop->ask_action = 1;
                    break;
                case SDLK_RETURN:
                    data->shop->ask_action = 5;
                    break;
                default: {

                    break;
                }
            }

            break;
        }

        default: {
            data->shop->ask_action = 0;
            break;
        }
    }
}

extern void renderScene_Scene_shop(SDL_Surface* window, ImageCollector* myImageCollector, FontCollector* myFontCollector, Data* data) {
    SDL_Surface* mainShopSurface = NULL;
    mainShopSurface = getShop(myImageCollector, myFontCollector, data);

    SDL_Rect mainShopSurfacePos;
    mainShopSurfacePos.x = 0;
    mainShopSurfacePos.y = 0;

    loadSurface(mainShopSurface, window, mainShopSurfacePos);

    SDL_FreeSurface(mainShopSurface);
}

extern void logicProcess_Scene_shop(Data* data) {
    if(data->shop->ask_action != 0) {
        printf("Choice: %d\n",data->shop->ask_action);
        if(data->shop->ask_action != 5) {
            //Moving
            moveShopSelector(data,data->shop->shop_inv,data->Isaac->inventory);
        } else if(data->shop->n_selected < 20) {
            //Buying
            buy_item(data,data->shop->selected);
        } else {
            //Selling
            sell_item(data,data->shop->selected);
        }
    }
}

static SDL_Surface* getShop(ImageCollector* myImageCollector, FontCollector* myFontCollector, Data* data) {
    SDL_Surface* shop = NULL;
    shop = SDL_CreateRGBSurface(SDL_HWSURFACE, 1280, 720, 32, 0, 0, 0, 0);

    SDL_Surface* bg = NULL;

    SDL_Surface* moneyInfo = NULL;
    SDL_Surface* dialog1Info = NULL;
    SDL_Surface* dialog2Info = NULL;
    SDL_Surface* shopInfo = NULL;
    SDL_Surface* inventoryInfo = NULL;

    SDL_Surface* selector = NULL;

    TTF_Font* font1 = NULL;

    font1 = get_FontCollector(myFontCollector, "menu/40")->font;
    SDL_Color black = {0, 0, 0, 0};
    SDL_Color white = {255, 255, 255, 0};

    SDL_Rect bgPos;

    SDL_Rect moneyInfoPos;
    SDL_Rect dialog1InfoPos;
    SDL_Rect dialog2InfoPos;
    SDL_Rect shopInfoPos;
    SDL_Rect inventoryInfoPos;

    SDL_Rect selectorPos;

    bg = get_ImageCollector(myImageCollector, "shop/interface")->surface;

    char dialog[200];
    sprintf(&dialog, "%s. That costs %d$. I've %d of them in stock...",data->shop->selected->name_item, data->shop->selected->price, data->shop->selected->quantity);
    dialog1Info = TTF_RenderText_Solid(font1, dialog , white);
    sprintf(&dialog,"%s",data->shop->selected->description);
    dialog2Info = TTF_RenderText_Solid(font1, dialog , white);
    sprintf(&dialog,"%d",data->Isaac->money);
    moneyInfo = TTF_RenderText_Solid(font1, dialog, white);
    shopInfo = TTF_RenderText_Solid(font1, "Shop", black);
    inventoryInfo = TTF_RenderText_Solid(font1, "Inventory", black);

    bgPos.x = 0;
    bgPos.y = 0;

    moneyInfoPos.x = 1000;
    moneyInfoPos.y = 70;

    dialog1InfoPos.x = 46;
    dialog1InfoPos.y = 500;

    dialog2InfoPos.x = 46;
    dialog2InfoPos.y = 540;

    shopInfoPos.x = 85;
    shopInfoPos.y = 15;

    inventoryInfoPos.x = 85;
    inventoryInfoPos.y = 260;

    selectorPos.x = 65 + (data->shop->n_selected % 10) * 77;
    selectorPos.y = 73 + (data->shop->n_selected / 10) * 77 + (data->shop->n_selected / 20) * 90;
    selector = get_ImageCollector(myImageCollector, "shop/cursor")->surface;

    SDL_BlitSurface(bg, NULL, shop, &bgPos);

    SDL_BlitSurface(dialog1Info, NULL, shop, &dialog1InfoPos);
    SDL_BlitSurface(dialog2Info, NULL, shop, &dialog2InfoPos);
    SDL_BlitSurface(moneyInfo, NULL, shop, &moneyInfoPos);
    SDL_BlitSurface(shopInfo, NULL, shop, &shopInfoPos);
    SDL_BlitSurface(inventoryInfo, NULL, shop, &inventoryInfoPos);
    SDL_BlitSurface(selector, NULL, shop, &selectorPos);

    SDL_FreeSurface(moneyInfo);
    SDL_FreeSurface(dialog1Info);
    SDL_FreeSurface(dialog2Info);
    SDL_FreeSurface(shopInfo);
    SDL_FreeSurface(inventoryInfo);

    return shop;
}

//Cursor displacement (right: 1; left: -1; down: 10; up: 10)
static void moveShopSelector(Data * data,slot_inventory * shop_list, slot_inventory * player_list) {
    int pos_to_go;
    switch(data->shop->ask_action) {
        //Case for right
        case 1:
            //First, case when we don't change of inventory, then if we have to (shop to player)
            if(data->shop->selected->next != NULL) {
                data->shop->selected = data->shop->selected->next;
                data->shop->n_selected++;
            } else if (data->shop->n_selected < 20 && player_list != NULL) {
                data->shop->selected = player_list;
                data->shop->n_selected = 20;
            }
            break;
            //Case for left
        case -1:
            //First, case when we don't change of inventory, then if we have to (player to shop)
            if(data->shop->selected->prev != NULL) {
                data->shop->selected = data->shop->selected->prev;
                data->shop->n_selected--;
            } else if (data->shop->n_selected >= 20) {
                data->shop->selected = shop_list;
                data->shop->n_selected = 0;
                while(data->shop->selected->next != NULL) {
                    data->shop->selected = data->shop->selected->next;
                    (data->shop->n_selected)++;
                }
            }
            break;
            //Case for down
        case 10: ;
            pos_to_go = (data->shop->n_selected + 10) % 40;
            //If we change of inventory
            if (data->shop->n_selected / 10 == 1 && player_list != NULL) {
                data->shop->selected = player_list;
                data->shop->n_selected = 20;
            }
            while (data->shop->selected->next != NULL && data->shop->n_selected != pos_to_go) {
                data->shop->selected = data->shop->selected->next;
                (data->shop->n_selected)++;
            }
            break;
            //Case for up
        case -10: ;
            if(data->shop->n_selected / 10 != 0) {
                pos_to_go = (data->shop->n_selected - 10) % 40;
                //If we change of inventory
                if (data->shop->n_selected / 10 == 2) {
                    data->shop->selected = shop_list;
                    data->shop->n_selected = 0;
                    while (data->shop->selected->next != NULL && data->shop->n_selected != pos_to_go) {
                        data->shop->selected = data->shop->selected->next;
                        (data->shop->n_selected)++;
                    }
                } else {
                    while (data->shop->selected->prev != NULL && data->shop->n_selected != pos_to_go) {
                        data->shop->selected = data->shop->selected->prev;
                        (data->shop->n_selected)--;
                    }
                }
            }
            else {
                data->shop->selected = data->shop->shop_inv;
                data->shop->n_selected = 0;
            }
            break;
        default:
            break;
    }
}

static void buy_item(Data * data, slot_inventory * item_buying) {
    slot_inventory * current_item;
    //If it is possible to buy
    if(alter_money(data->Isaac,- item_buying->price) == 1) {
        current_item = search_item_list(data->Isaac->inventory,item_buying->name_item);
        if(current_item != NULL) {
            //If the player already has an exemplar of the item in its inventory
            (current_item->quantity)++;
        } else {
            //If the player is buying a new item, we create it inside its inventory
            add_item_list(&(data->Isaac->inventory),create_item(item_buying->name_item,1,item_buying->price,item_buying->description),&(data->Isaac->size_inventory));
        }
    }
}

static void sell_item(Data * data, slot_inventory * item_selling) {
    alter_money(data->Isaac,item_selling->price);
    (item_selling->quantity)--;
    //Checking if the item has to be removed from the inventory
    if(item_selling->quantity <= 0) {
        //Loop to replace the cursor
        if(item_selling->next != NULL) {
            data->shop->selected = item_selling->next;
        } else if (item_selling->prev != NULL) {
            data->shop->selected = item_selling->prev;
            data->shop->n_selected--;
        } else {
            data->shop->selected = data->shop->shop_inv;
            data->shop->n_selected = 0;
        }
        //Finally removing the item
        remove_item_list(&(data->Isaac->inventory),item_selling->name_item,&(data->Isaac->size_inventory));
        free_item(item_selling);
    }
}