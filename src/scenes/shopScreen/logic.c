#include "logic.h"

static void moveShopSelector(Data * data,SlotInventory * shop_list, SlotInventory * player_list);
static void buy_item(Data * data, SlotInventory * item_buying);
static void sell_item(Data * data, SlotInventory * item_selling);

//Cursor displacement (right: 1; left: -1; down: 10; up: 10)
static void moveShopSelector(Data * data,SlotInventory * shop_list, SlotInventory * player_list) {
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
            if ((player_list != NULL && (data->shop->n_selected / 10 == 1|| (data->shop->n_selected / 10 == 0 && data->shop->size_shop <= 10)))) {
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

static void buy_item(Data * data, SlotInventory * item_buying) {
    SlotInventory * current_item;
    //If it is possible to buy
    if(alter_money(data->Isaac,- item_buying->price) == 1) {
        current_item = search_SlotInventory(data->Isaac->inventory, item_buying->id);
        if(current_item != NULL) {
            //If the player already has an exemplar of the item in its inventory
            (current_item->quantity)++;
        } else {
            //If the player is buying a new item, we create it inside its inventory
            add_SlotInventory(&(data->Isaac->inventory),
                              create_SlotInventory(item_buying->id,1,data->referenceItems),
                              &(data->Isaac->size_inventory));
        }
    }
}

static void sell_item(Data * data, SlotInventory * item_selling) {
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
        remove_SlotInventory(&(data->Isaac->inventory), item_selling->id, &(data->Isaac->size_inventory));
        freeOne_SlotInventory(&item_selling);
    }
}

extern void logicProcess_Scene_shop(Engine* engine, Data* data) {
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
        data->shop->ask_action = 0;
    }
}