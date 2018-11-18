#include "logic.h"

static void moveInventorySelector(Data* data);
static void useItem(Data* data);

extern void logicProcess_Scene_inventory(Engine* engine, Data* data) {
}

//Cursor displacement (right: 1; left: -1; down: 10; up: 10)
static void moveInventorySelector(Data* data) {
    int pos_to_go;
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
            pos_to_go = (data->inventory->nSelected + 10) % 40;
            //If go to the button
            if ((data->inventory->nSelected / 10 == 1 || (data->inventory->nSelected / 10 == 0 && data->Isaac->size_inventory <= 10))) {
                data->inventory->selected = NULL;
                data->inventory->nSelected = 20;
            } else {
                while (data->inventory->selected->next != NULL && data->inventory->nSelected != pos_to_go) {
                    data->inventory->selected = data->inventory->selected->next;
                    (data->inventory->nSelected)++;
                }
                break;
            }
            //Case for up
        case -10: ;
            if(data->inventory->nSelected / 10 != 0) {
                pos_to_go = (data->inventory->nSelected - 10) % 40;
                //If we go from the button to the inventory
                if (data->inventory->nSelected / 10 == 2) {
                    data->inventory->selected = data->Isaac->inventory;
                    data->inventory->nSelected = 0;
                    while (data->inventory->selected->next != NULL && data->inventory->nSelected != pos_to_go) {
                        data->inventory->selected = data->inventory->selected->next;
                        (data->inventory->nSelected)++;
                    }
                } else {
                    while (data->inventory->selected->prev != NULL && data->inventory->nSelected != pos_to_go) {
                        data->inventory->selected = data->inventory->selected->prev;
                        (data->inventory->nSelected)--;
                    }
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

static void useItem(Data* data) {
    //TODO: Fill that shit
}