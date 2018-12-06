#include "logic.h"

static void moveShopSelector(Data* data);
static void buy_item(Data* data, SlotInventory * itemBuying, int number);
static void sell_item(Data* data, SlotInventory * itemSelling, int number);
static void moveConfirmCursor(Data* data);

extern void logicProcess_Scene_shop(Engine* engine, Data* data) {
    int action = data->shop->askAction;

    if(isStarted_Timer(data->shop->timerMessage)){
        if((getTime_Timer(data->shop->timerMessage) > 3 && strcmp(data->shop->messageAction,"Init") != 0)
        || (getTime_Timer(data->shop->timerMessage) > 10 && strcmp(data->shop->messageAction,"Init") == 0)) {
            stop_Timer(data->shop->timerMessage);
            strcpy(data->shop->messageAction,"");
        }
    }

    if(data->shop->askTransaction != -1 || action == I_ENTER) {
        moveConfirmCursor(data);
        data->shop->askAction = I_NONE;
    } else if(action != I_NONE && action != I_LEAVE) {
        //Moving
        moveShopSelector(data);
        data->shop->askAction = I_NONE;
    } else if (action == I_LEAVE) {
        data->shop->askAction = I_NONE;
        display_SceneCollector(engine, data, "lobby");
    }

}

//Cursor displacement (right: 1; left: -1; down: 10; up: -10)
static void moveShopSelector(Data* data) {
    int pos_to_go = 0, tempPos = 0;
    SlotInventory* tempSlot = NULL;
    switch(data->shop->askAction) {
        case 1: {
            //Case for right
            if(data->shop->nSelected % 4 == 3 || data->shop->selected->next == NULL) {
                if(data->shop->nSelected < 16 && data->shop->shop_inv) {
                    pos_to_go = data->shop->nSelected + 13 - (data->shop->nSelected % 4 - 3);
                    data->shop->selected = data->shop->shop_inv;
                    data->shop->nSelected = 16;

                    tempSlot = data->shop->selected;
                    tempPos = data->shop->nSelected;

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
                if(data->shop->nSelected >= 16  && data->Isaac->inventory) {
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
                    if(data->shop->nSelected % 4 != 3 && data->shop->selected->next != NULL) {
                        data->shop->selected = tempSlot;
                        data->shop->nSelected = tempPos;
                    }
                }
            } else {
                if (data->shop->selected->prev != NULL) {
                    data->shop->selected = data->shop->selected->prev;
                    (data->shop->nSelected)--;
                }
            }
            break;
        }
        case -10: {
            //Case for up
            if(data->shop->nSelected / 4 != 0 && data->shop->nSelected / 4 != 4) {
                pos_to_go = data->shop->nSelected - 4;
                while (data->shop->selected->prev != NULL && data->shop->nSelected != pos_to_go) {
                    data->shop->selected = data->shop->selected->prev;
                    (data->shop->nSelected)--;
                }
            } else {
                if(data->shop->nSelected < 16) {
                    data->shop->selected = data->Isaac->inventory;
                    data->shop->nSelected = 0;
                } else {
                    data->shop->selected = data->shop->shop_inv;
                    data->shop->nSelected = 16;
                }

            }
            break;
        }
        case 10: {
            //Case for down
            if(data->shop->nSelected / 4 != 3 && data->shop->nSelected / 4 != 7) {
                pos_to_go = data->shop->nSelected + 4;
            } else if(data->shop->nSelected / 4 != 3) {
                pos_to_go = 15;
            } else {
                pos_to_go = 31;
            }
            while (data->shop->selected->next != NULL && data->shop->nSelected != pos_to_go) {
                data->shop->selected = data->shop->selected->next;
                (data->shop->nSelected)++;
            }
            break;
        }
        default:
            break;
    }
}

static void buy_item(Data * data, SlotInventory * itemBuying, int number) {
    SlotInventory * current_item;
    int j = 0;
    char nameItem[25];
    for(int i = 0; i < number; i++) {
        //If it is possible to buy
        if(alterMoney(data->Isaac, - itemBuying->price) == 1) {
            ++j;
            strcpy(nameItem, itemBuying->name);
            current_item = search_SlotInventory(data->Isaac->inventory, itemBuying->id);
            if(current_item != NULL) {
                //If the player already has an exemplar of the item in its inventory
                (current_item->quantity)++;
            } else {
                //If the player is buying a new item, we create it inside its inventory
                add_SlotInventory(&(data->Isaac->inventory),
                                  create_SlotInventory(itemBuying->id,1,data->referenceItems),
                                  &(data->Isaac->size_inventory));
            }
        }
    }
    if(j != 0) {
        sprintf(data->shop->messageAction, "You bought %d %s!", j, nameItem);
        start_Timer(data->shop->timerMessage);
    }
}

static void sell_item(Data * data, SlotInventory * itemSelling, int number) {
    int i;
    char nameItem[25];
    for(i = 0; i < number; i++) {
        strcpy(nameItem, itemSelling->name);
        alterMoney(data->Isaac, (int) (itemSelling->price * .8));
        (itemSelling->quantity)--;
        //Checking if the item has to be removed from the inventory
        if(itemSelling->quantity <= 0) {
            //Loop to replace the cursor
            if(itemSelling->next != NULL) {
                data->shop->selected = itemSelling->next;
            } else if (itemSelling->prev != NULL) {
                data->shop->selected = itemSelling->prev;
                data->shop->nSelected--;
            } else {
                data->shop->selected = data->shop->shop_inv;
                data->shop->nSelected = 0;
            }
            //Finally removing the item
            remove_SlotInventory(&(data->Isaac->inventory), itemSelling->id, &(data->Isaac->size_inventory));
            freeOne_SlotInventory(&itemSelling);

            if(data->Isaac->inventory == NULL) {
                data->shop->nSelected = 16;
                data->shop->selected = data->shop->shop_inv;
            }
        }
    }
    if(i != 0) {
        sprintf(data->shop->messageAction, "You sold %d %s!", i, nameItem);
        start_Timer(data->shop->timerMessage);
    }
}

// -1: Idle to start process; 0: Button CANCEL; 1: Button CONFIRM
static void moveConfirmCursor(Data* data) {
    if(data->shop->selected) {
        switch(data->shop->askTransaction) {
            case -1: {
                //Entering inside the confirmation loop
                data->shop->askTransaction = 2;
                break;
            }
            case 0: {
                //Button 'CANCEL'
                if(data->shop->askAction == -1) {
                    data->shop->askTransaction = 1;
                }else if(data->shop->askAction == -10){
                    data->shop->askTransaction = 2;
                }else if(data->shop->askAction == 5) {
                    data->shop->askTransaction = -1;
                    data->shop->itemsInTransaction = 0;
                }
                break;
            }
            case 1: {
                //Button 'CONFIRM'
                if(data->shop->askAction == 1) {
                    data->shop->askTransaction = 0;
                }else if(data->shop->askAction == -10) {
                    data->shop->askTransaction = 2;
                }else if(data->shop->askAction == 5) {
                    //Action
                    if(data->shop->nSelected >= 16) {
                        //Buying
                        buy_item(data,data->shop->selected,data->shop->itemsInTransaction);
                    } else {
                        //Selling
                        sell_item(data,data->shop->selected,data->shop->itemsInTransaction);
                    }
                    data->shop->askTransaction = -1;
                    data->shop->itemsInTransaction = 0;
                }
                break;
            }
            case 2: {
                //Select number of item
                if(data->shop->askAction == 1 && data->shop->itemsInTransaction < data->shop->selected->quantity) {
                    (data->shop->itemsInTransaction)++;
                } else if (data->shop->askAction == -1 && data->shop->itemsInTransaction > 0) {
                    (data->shop->itemsInTransaction)--;
                } else if (data->shop->askAction == 10) {
                    data->shop->askTransaction = 1;
                }
                break;
            }
            default: break;
        }
    }
}