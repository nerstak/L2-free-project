#include "logic.h"

static void moveInventorySelector(Data* data);
static void deleteItemInventory(Data* data);
static void useItem(Data* data);
static void applyEffect(Data* data);
static void moveDeleteCursor(Data* data);

extern void logicProcess_Scene_inventory(Engine* engine, Data* data) {
    int action = data->inventory->askAction;

    if(isStarted_Timer(data->inventory->timerMessage)){
        if(getTime_Timer(data->inventory->timerMessage) > 3) {
            stop_Timer(data->inventory->timerMessage);
            strcpy(data->inventory->messageUsed,"");
        }
    }

    if(data->inventory->askDeletion != -1 || action == I_DELETE) {
        if(action == I_DELETE) {
            data->inventory->askDeletion = -1;
        }
        moveDeleteCursor(data);
        data->inventory->askAction = I_NONE;
    } else if(action != I_NONE) {
        if(action != I_ENTER && action != I_DELETE && action != I_LEAVE) {
            moveInventorySelector(data);
            data->inventory->askAction = I_NONE;
        } else if(action == I_ENTER) {
            useItem(data);
            data->inventory->askAction = I_NONE;
        } else if(action == I_LEAVE) {
            data->inventory->askAction = I_NONE;
            display_SceneCollector(engine, data, engine->sceneCollector->previousScene->name);
        }
    }
}

//Cursor displacement (right: 1; left: -1; down: 10; up: 10)
static void moveInventorySelector(Data* data) {
    int pos_to_go;
    if(data->inventory->selected) {
        switch(data->inventory->askAction) {
            case I_RIGHT: {
                //Case for right
                //If we are just moving inside the inventory
                if (data->inventory->selected->next != NULL) {
                    data->inventory->selected = data->inventory->selected->next;
                    (data->inventory->nSelected)++;
                }
                break;
            }
            case I_LEFT: {
                //Case for left
                //If we are just moving inside the inventory
                if (data->inventory->selected->prev != NULL) {
                    data->inventory->selected = data->inventory->selected->prev;
                    (data->inventory->nSelected)--;
                }
                break;
            }
            case I_DOWN: {
                //Case for down
                pos_to_go = (data->inventory->nSelected + 4) % 16;
                while (data->inventory->selected->next != NULL && data->inventory->nSelected != pos_to_go) {
                    data->inventory->selected = data->inventory->selected->next;
                    (data->inventory->nSelected)++;
                }
                break;
            }
            case I_UP: {
                //Case for up
                if (data->inventory->nSelected / 4 != 0) {
                    pos_to_go = (data->inventory->nSelected - 4) % 16;
                    while (data->inventory->selected->prev != NULL && data->inventory->nSelected != pos_to_go) {
                        data->inventory->selected = data->inventory->selected->prev;
                        (data->inventory->nSelected)--;
                    }
                } else {
                    data->inventory->selected = data->Isaac->inventory;
                    data->inventory->nSelected = 0;
                }
                break;
            }
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
    if(data->inventory->selected) {
        if(data->inventory->selected->type != 'n' && data->inventory->selected->type != 's') {
            strcpy(data->inventory->messageUsed, data->inventory->selected->useMessage);
            applyEffect(data);
            (data->inventory->selected->quantity)--;
            if(data->inventory->selected->quantity <= 0) {
                deleteItemInventory(data);
            }
            start_Timer(data->inventory->timerMessage);
        }
    }
}

static void applyEffect(Data* data) {
    SlotInventory* current = data->inventory->selected;
    switch(current->type) {
        case 'p': {
            alterHealth(data->Isaac, current->characteristics->health * data->Isaac->current_stats->health, 'c');
            alterAgility(data->Isaac, current->characteristics->agility * data->Isaac->current_stats->agility, 'c');
            alterSpeed(data->Isaac, current->characteristics->agility * data->Isaac->current_stats->speed, 'c');
            alterDamage(data->Isaac, current->characteristics->damage * data->Isaac->current_stats->damage, 'c');
            break;
        }
        case 'v': {
            alterHealth(data->Isaac, current->characteristics->health * data->Isaac->basic_stats->health, 'b');
            alterAgility(data->Isaac, current->characteristics->agility * data->Isaac->basic_stats->agility, 'b');
            alterSpeed(data->Isaac, current->characteristics->agility * data->Isaac->basic_stats->speed, 'b');
            alterDamage(data->Isaac, current->characteristics->damage * data->Isaac->basic_stats->damage, 'b');
            break;
        }
        default: {
            break;
        }
    }
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
                if(data->inventory->askAction == I_LEFT) {
                    data->inventory->askDeletion = 1;
                } else if(data->inventory->askAction == I_ENTER) {
                    data->inventory->askDeletion = -1;
                }
                break;
            }
            case 1: {
                //Button 'CONFIRM'
                if(data->inventory->askAction == I_RIGHT) {
                    data->inventory->askDeletion = 0;
                } else if(data->inventory->askAction == I_ENTER) {
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