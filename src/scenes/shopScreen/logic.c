#include "logic.h"

static void moveShopSelector(Data* data);
static void buy_item(Data* data, SlotInventory * item_buying, int number);
static void sell_item(Data* data, SlotInventory * item_selling, int number);
static void moveConfirmCursor(Data* data);

extern void logicProcess_Scene_shop(Engine* engine, Data* data) {
    int action = data->shop->askAction;
    if(data->shop->askTransaction != -1 || action == 5) {
        moveConfirmCursor(data);
    } else if(action != 0) {
        if(action != 5) {
            //Moving
            moveShopSelector(data);
        }
    }
    data->shop->askAction = 0;
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
                while (data->shop->selected->next != NULL && data->shop->nSelected != pos_to_go) {
                    data->shop->selected = data->shop->selected->next;
                    (data->shop->nSelected)++;
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
        default:
            break;
    }
}

static void buy_item(Data * data, SlotInventory * item_buying, int number) {
    SlotInventory * current_item;
    for(int i = 0; i < number; i++) {
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
}

static void sell_item(Data * data, SlotInventory * item_selling, int number) {
    for(int i = 0; i < number; i++) {
        alter_money(data->Isaac,(int)(item_selling->price * .8));
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

            if(data->Isaac->inventory == NULL) {
                data->shop->nSelected = 16;
                data->shop->selected = data->shop->shop_inv;
            }
        }
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
        }
    }
}