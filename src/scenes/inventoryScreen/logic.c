#include "logic.h"

static void moveInventorySelector(Data* data);
static void deleteItemInventory(Data* data);
static void useItem(Data* data);
static void moveDeleteCursor(Data* data);

extern void logicProcess_Scene_inventory(Engine* engine, Data* data) {
    int action = data->inventory->askAction;
    if(data->inventory->askDeletion != -1) {
        moveDeleteCursor(data);
    } else if(action != 0) {
        if(action != 5 && action != 8) {
            moveInventorySelector(data);
        } else if(action == 5) {
            useItem(data);
        } else if(action == 8) {
            moveDeleteCursor(data);
        }
    }
    data->inventory->askAction = 0;
}

//Cursor displacement (right: 1; left: -1; down: 10; up: 10)
static void moveInventorySelector(Data* data) {
    int pos_to_go;
    if(data->inventory->selected) {
        switch(data->inventory->askAction) {
            //Case for right
            case 1:
                //If we are just moving inside the inventory
                if(data->inventory->selected->next != NULL) {
                    data->inventory->selected = data->inventory->selected->next;
                    (data->inventory->nSelected)++;
                }
                break;
                //Case for left
            case -1:
                //If we are just moving inside the inventory
                if(data->inventory->selected->prev != NULL) {
                    data->inventory->selected = data->inventory->selected->prev;
                    (data->inventory->nSelected)--;
                }
                break;
                //Case for down
            case 10: ;
                pos_to_go = (data->inventory->nSelected + 4) % 16;
                while (data->inventory->selected->next != NULL && data->inventory->nSelected != pos_to_go) {
                    data->inventory->selected = data->inventory->selected->next;
                    (data->inventory->nSelected)++;
                }
                break;
                //Case for up
            case -10: ;
                if(data->inventory->nSelected / 4 != 0) {
                    pos_to_go = (data->inventory->nSelected - 4) % 16;
                    while (data->inventory->selected->prev != NULL && data->inventory->nSelected != pos_to_go) {
                        data->inventory->selected = data->inventory->selected->prev;
                        (data->inventory->nSelected)--;
                    }
                }
                else {
                    data->inventory->selected = data->Isaac->inventory;
                    data->inventory->nSelected = 0;
                }
                break;
            default:
                break;
        }
    }
}

static void deleteItemInventory(Data* data) {
    if(data->inventory->selected) {
        SlotInventory* itemDeleting = data->inventory->selected;

        //Change of position of the cursor
        if(itemDeleting->next != NULL) {
            data->inventory->selected = itemDeleting->next;
        } else if (itemDeleting->prev != NULL) {
            data->inventory->selected = itemDeleting->prev;
            (data->inventory->nSelected)--;
        } else {
            data->inventory->selected = NULL;
            data->inventory->nSelected = 0;
        }

        //Free the item
        remove_SlotInventory(&(data->Isaac->inventory), itemDeleting->id, &(data->Isaac->size_inventory));
        freeOne_SlotInventory(&itemDeleting);
    }
}

static void useItem(Data* data) {
    //First we should check if the item is usable
    //But because we don't have a proper list of items, we can't

    if(data->inventory->selected) {
        (data->inventory->selected->quantity)--;
        if(data->inventory->selected->quantity <= 0) {
            deleteItemInventory(data);
        }
    }


    //TODO: Fill that shit
}

static void moveDeleteCursor(Data* data) {
    if(data->inventory->selected) {
        switch(data->inventory->askDeletion) {
            case -1: {
                //Entering inside the confirmation loop
                data->inventory->askDeletion = 1;
                break;
            }
            case 0: {
                //Button 'CANCEL'
                if(data->inventory->askAction == -1) {
                    data->inventory->askDeletion = 1;
                } else if(data->inventory->askAction == 5) {
                    data->inventory->askDeletion = -1;
                }
                break;
            }
            case 1: {
                //Button 'CONFIRM'
                if(data->inventory->askAction == 1) {
                    data->inventory->askDeletion = 0;
                } else if(data->inventory->askAction == 5) {
                    data->inventory->askDeletion = 2;
                }
                break;
            }
            case 2: {
                //Suppression
                deleteItemInventory(data);
                data->inventory->askDeletion = -1;
                break;
            }
        }
    }
}