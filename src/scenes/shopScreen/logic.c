#include "logic.h"

static void moveShopSelector(Data* data);
static void buy_item(Data* data, SlotInventory * item_buying);
static void sell_item(Data* data, SlotInventory * item_selling);

extern void logicProcess_Scene_shop(Engine* engine, Data* data) {
    if(data->shop->askAction != 0) {
        printf("Choice: %d\n",data->shop->askAction);
        if(data->shop->askAction != 5) {
            //Moving
            moveShopSelector(data);
        } else if(data->shop->nSelected < 20) {
            //Buying
            buy_item(data,data->shop->selected);
        } else {
            //Selling
            sell_item(data,data->shop->selected);
        }
        data->shop->askAction = 0;
    }
}

//Cursor displacement (right: 1; left: -1; down: 10; up: -10)
static void moveShopSelector(Data* data) {
    int pos_to_go = 0, tempPos = 0;
    SlotInventory* tempSlot = NULL;
    switch(data->shop->askAction) {
        case 1: {
            //Case for right
            if(data->shop->nSelected % 4 == 3) {
                if(data->shop->nSelected < 20 ) {
                    pos_to_go = data->shop->nSelected + 13;
                    data->shop->selected = data->shop->shop_inv;
                    data->shop->nSelected = 20;

                    while(data->shop->selected->next != NULL && data->shop->nSelected != pos_to_go) {
                        data->shop->selected = data->shop->selected->next;
                        (data->shop->nSelected)++;

                        if(data->shop->nSelected % 4 == 0) {
                            tempSlot = data->shop->selected;
                            tempPos = data->shop->nSelected;
                        }
                    }
                    if(data->shop->nSelected % 4 != 0) {
                        data->shop->selected = tempSlot;
                        data->shop->nSelected = tempPos;
                    }
                }
            } else {
                if (data->shop->selected->next != NULL) {
                    data->shop->selected = data->shop->selected->next;
                    (data->shop->nSelected)++;
                }
            }
                break;
        }

        case -1: {
            //Case for left
            if(data->shop->nSelected % 4 == 0) {
                if(data->shop->nSelected >= 20 ) {
                    pos_to_go = data->shop->nSelected - 13;
                    data->shop->selected = data->Isaac->inventory;
                    data->shop->nSelected = 0;

                    while(data->shop->selected->next != NULL && data->shop->nSelected != pos_to_go) {
                        data->shop->selected = data->shop->selected->next;
                        (data->shop->nSelected)++;

                        if(data->shop->nSelected % 4 == 3) {
                            tempSlot = data->shop->selected;
                            tempPos = data->shop->nSelected;
                        }
                    }
                    if(data->shop->nSelected % 4 != 3) {
                        data->shop->selected = tempSlot;
                        data->shop->nSelected = tempPos;
                    }
                }
            } else {
                if (data->shop->selected->next != NULL) {
                    data->shop->selected = data->shop->selected->next;
                    (data->shop->nSelected)++;
                }
            }
            break;
        }
        case -10: {
            //Case for up
            if(data->shop->nSelected / 4 != 0 && data->shop->nSelected / 4 != 5) {
                pos_to_go = data->shop->nSelected - 4;
                while (data->shop->selected->prev != NULL && data->shop->nSelected != pos_to_go) {
                    data->shop->selected = data->shop->selected->prev;
                    (data->shop->nSelected)--;
                }
            }
            break;
        }
        case 10: {
            //Case for down
            if(data->shop->nSelected / 4 != 3 && data->shop->nSelected / 4 != 8) {
                pos_to_go = data->shop->nSelected + 4;
                while (data->shop->selected->next != NULL && data->shop->nSelected != pos_to_go) {
                    data->shop->selected = data->shop->selected->next;
                    (data->shop->nSelected)++;
                }
            }
            break;
        }
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
            data->shop->nSelected--;
        } else {
            data->shop->selected = data->shop->shop_inv;
            data->shop->nSelected = 0;
        }
        //Finally removing the item
        remove_SlotInventory(&(data->Isaac->inventory), item_selling->id, &(data->Isaac->size_inventory));
        freeOne_SlotInventory(&item_selling);
    }
}