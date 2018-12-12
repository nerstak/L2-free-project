#include "logic.h"

static void moveInventorySelector(Engine* engine, Data* data);
static void deleteItemInventory(Data* data);
static void useItem(Engine* engine, Data* data);
static void applyEffect(Engine* engine, Data* data);
static void moveDeleteCursor(Engine* engine, Data* data);

extern void logicProcess_Scene_inventory(Engine* engine, Data* data) {
    int action = data->inventory->askAction;

    if(isStarted_Timer(data->inventory->timerMessage)){
        if(getTime_Timer(data->inventory->timerMessage) > 3 || action != I_NONE) {
            stop_Timer(data->inventory->timerMessage);
            strcpy(data->inventory->messageUsed,"");
        }
    }

    if(data->inventory->askDeletion != -1 || action == I_DELETE) {
        if(action == I_DELETE) {
            data->inventory->askDeletion = -1;
        }
        moveDeleteCursor(engine, data);
        data->inventory->askAction = I_NONE;
    } else if(action != I_NONE) {
        if(action != I_ENTER && action != I_LEAVE) {
            moveInventorySelector(engine, data);
            data->inventory->askAction = I_NONE;
        } else if(action == I_ENTER) {
            useItem(engine, data);
            data->inventory->askAction = I_NONE;
        } else if(action == I_LEAVE) {
            data->inventory->askAction = I_NONE;
            playEffect(engine->soundCollector, "loading/leave_menu", 0);
            display_SceneCollector(engine, data, engine->sceneCollector->previousScene->name);
        }
    }
}

//Cursor displacement (right: 1; left: -1; down: 10; up: 10)
static void moveInventorySelector(Engine* engine, Data* data) {
    int pos_to_go, moved = 0;
    if(data->inventory->selected) {
        switch(data->inventory->askAction) {
            case I_RIGHT: {
                //Case for right
                //If we are just moving inside the inventory
                if (data->inventory->selected->next != NULL) {
                    data->inventory->selected = data->inventory->selected->next;
                    (data->inventory->nSelected)++;
                    moved = 1;
                }
                break;
            }
            case I_LEFT: {
                //Case for left
                //If we are just moving inside the inventory
                if (data->inventory->selected->prev != NULL) {
                    data->inventory->selected = data->inventory->selected->prev;
                    (data->inventory->nSelected)--;
                    moved = 1;
                }
                break;
            }
            case I_DOWN: {
                //Case for down
                pos_to_go = (data->inventory->nSelected + 4) % 16;
                while (data->inventory->selected->next != NULL && data->inventory->nSelected != pos_to_go) {
                    data->inventory->selected = data->inventory->selected->next;
                    (data->inventory->nSelected)++;
                    moved = 1;
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
                        moved = 1;
                    }
                } else if(data->inventory->nSelected != 0) {
                    data->inventory->selected = data->Isaac->inventory;
                    data->inventory->nSelected = 0;
                    moved = 1;
                }
                break;
            }
            default:
                break;
        }
    }
    if(moved == 1) {
        playEffect(engine->soundCollector, "inventory/move_button", 0);
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
        remove_SlotInventory(&(data->Isaac->inventory), itemDeleting->id, &(data->Isaac->sizeInventory));
        freeOne_SlotInventory(&itemDeleting);
    }
}

static void useItem(Engine* engine, Data* data) {
    //First we should check if the item is usable
    if(data->inventory->selected) {
        if(data->inventory->selected->type != 'n' && data->inventory->selected->type != 's') {
            strcpy(data->inventory->messageUsed, data->inventory->selected->useMessage);
            applyEffect(engine, data);
            (data->inventory->selected->quantity)--;
            if(data->inventory->selected->quantity <= 0) {
                deleteItemInventory(data);
            }
            start_Timer(data->inventory->timerMessage);
        }
    }
}

static void applyEffect(Engine* engine, Data* data) {
    SlotInventory* current = data->inventory->selected;
    int use = 0;
    switch(current->type) {
        case 'p': {
            playEffect(engine->soundCollector, "player/drink", 0);
            if(current->id - 12 >= 0 && current->id - 12 < 6) {
                if(data->Isaac->stats->potionsUsed[current->id - 12] == 0) {
                    use = 1;
                    data->Isaac->stats->potionsUsed[current->id - 12] = 1;
                }
            } else {
                use = 1;
            }
            if(use == 1) {
                //The health potions give back a certain amount of health, not depending of the player stat
                alterHealth_Player(data->Isaac, current->characteristics->health, 'c');
                alterAgility_Player(data->Isaac, current->characteristics->agility * data->Isaac->stats->current->agility, 'c');
                alterSpeed_Player(data->Isaac, current->characteristics->speed * data->Isaac->stats->current->speed, 'c');
                alterDamage_Player(data->Isaac, current->characteristics->damage * data->Isaac->stats->current->damage, 'c');
            }
            break;
        }
        case 'v': {
            playEffect(engine->soundCollector, "player/eat", 0);
            alterHealth_Player(data->Isaac, current->characteristics->health * data->Isaac->stats->basic->health, 'b');
            alterAgility_Player(data->Isaac, current->characteristics->agility * data->Isaac->stats->basic->agility,'b');
            alterSpeed_Player(data->Isaac, current->characteristics->speed * data->Isaac->stats->basic->speed, 'b');
            alterDamage_Player(data->Isaac, current->characteristics->damage * data->Isaac->stats->basic->damage, 'b');
            break;
        }
        default: {
            break;
        }
    }
}

static void moveDeleteCursor(Engine* engine, Data* data) {
    int moved = 0;
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
                    moved = 1;
                } else if(data->inventory->askAction == I_ENTER) {
                    playEffect(engine->soundCollector, "inventory/confirm_button", 0);
                    data->inventory->askDeletion = -1;
                }
                break;
            }
            case 1: {
                //Button 'CONFIRM'
                if(data->inventory->askAction == I_RIGHT) {
                    data->inventory->askDeletion = 0;
                    moved = 1;
                } else if(data->inventory->askAction == I_ENTER) {
                    playEffect(engine->soundCollector, "inventory/confirm2_button", 0);
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
    if(moved == 1) {
        playEffect(engine->soundCollector, "inventory/move_button", 0);
    }
}