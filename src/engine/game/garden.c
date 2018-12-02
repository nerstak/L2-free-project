#include <stdlib.h>
#include <stdio.h>

#include "garden.h"

#include "../save.h"
#include "plants.h"

static void test_plant(Data* data);
static int ToPlant(int x, Data* data);

extern void doAction_Garden(Data* data) {
    data->lobby->askAction = NONE;

    switch (checkAction_Garden(data)) {
        case 0: {
            break;
        }
        case 1: {
            data->lobby->actionProcess = SLEEP;
            data->lobby->askMove = 0;

            break;
        }
        case 2: {
            data->lobby->actionProcess = GARDEN;
            data->lobby->askMove = 0;

            break;
        }
        case 3: {
            data->lobby->actionProcess = SHOP;
            data->lobby->askMove = 0;
            break;
        }
        default: {
            break;
        }
    }
}

extern int checkAction_Garden(Data* data) {
    if (checkTilesPlayer(data->Isaac, data->lobby->layout, 'M', 48, 0, 0, NULL, NULL)) {
        //Case for home
        return 1;
    }

    if (checkTilesPlayer(data->Isaac, data->lobby->layout, 'P', 30, 0, 0, NULL, NULL)) {
        //Case for plant spot
        return 2;
    }

    if (checkTilesPlayer(data->Isaac, data->lobby->layout, 'S', 48, 0, 0, NULL, NULL)) {
        //Case for shop
        return 3;
    }

    return 0;
}

extern void processSleep(Data* data) {
    if(data->lobby->askAction == LEFT && data->lobby->cursor == 1) {
        data->lobby->cursor = 0;
    } else if(data->lobby->askAction == RIGHT && data->lobby->cursor == 0) {
        data->lobby->cursor = 1;
    } else if(data->lobby->askAction == SELECT) {
        if(data->lobby->cursor == 1) {
            writeSave(data);
            DayPass(data);
        }
        data->lobby->askAction = NONE;
        data->lobby->actionProcess = NONE;
        data->lobby->cursor = 0;
    }
}

extern void processMenu2_Garden(Data* data) {
    test_plant(data);
    processField_Garden(data);
}

static void test_plant(Data* data) {
    int coordX, coordY;
    if (checkTilesPlayer(data->Isaac, data->lobby->layout, 'P', 30, 0, 0, &coordX, &coordY)) {
        if (coordX == 15 ) {
            if (coordY == 5) {
                data->lobby->actualPlant = data->field->plantBotLeft;
            } else if (coordY == 2) {
                data->lobby->actualPlant = data->field->plantTopLeft;
            }
        } else if (coordX == 17) {
            if (coordY == 5) {
                data->lobby->actualPlant = data->field->plantBotRight;
            } else if (coordY == 2) {
                data->lobby->actualPlant = data->field->plantTopRight;
            }
        } else {
            data->lobby->actualPlant = NULL;
        }
    } else {
        data->lobby->actualPlant = NULL;
    }
}

extern void processField_Garden(Data* data) {
    if (data->lobby->actualPlant->idVegetable == -1) {
        data->lobby->actionProcess = PLANT; // plant ?
    } else if (data->lobby->actualPlant->dayLeft == 0) {
        data->lobby->actionProcess = GOTO_DUNGEON; //go to dj?
    } else if (data->lobby->actualPlant->dayLeft != 0) {
        data->lobby->actionProcess = WAIT;
    }
}

extern void menuSelectionDungeon_Garden(Data* data) {
    if (data->lobby->askAction == 0) {
        if (data->lobby->askMove > 1) {
            data->lobby->askMove = 1;
        }
        if (data->lobby->askMove < 0) {
            data->lobby->askMove = 0;
        }
    }
    else if (data->lobby->askAction == 1) {
        if (data->lobby->askMove == 0) {
            //go to donjon
        }
        else {

        }

        data->lobby->askAction = 0;
        data->lobby->actionProcess = NONE;
    }
}

extern void menuSelectionPlanting_Garden(Data* data) {
    if (data->lobby->askAction == NONE) {
        if (data->lobby->askMove > 5) {
            data->lobby->askMove = 5;
        }

        if (data->lobby->askMove < 0) {
            data->lobby->askMove = 0;
        }
    }
    else if (data->lobby->askAction == 1) {
        if (data->lobby->askMove != 5) {
            if(ToPlant(data->lobby->askMove, data) == 1){
                data->lobby->actionProcess = NONE;
            }
            else {
                data->lobby->actionProcess = NOT_ENOUGH;
            }
        }
        else if (data->lobby->askMove == 5){
            data->lobby->actionProcess = NONE;
        }
        data->lobby->actualPlant = NULL;
    }
}

static int ToPlant(int x, Data* data){
    SlotInventory* plant = search_SlotInventory(data->Isaac->inventory, x);

    if(plant){
        switch(x) {
            case 0: {
                data->lobby->actualPlant->dayLeft = 1;

                break;
            }
            case 1: {
                data->lobby->actualPlant->dayLeft = 2;

                break;
            }
            case 2: {
                data->lobby->actualPlant->dayLeft = 0;

                break;
            }
            case 3 : {
                data->lobby->actualPlant->dayLeft = 3;

                break;
            }
            case 4 :{
                data->lobby->actualPlant->dayLeft = 3;

                break;
            }

            default:
                // TODO: Fix here ?

                break;
        }

        data->lobby->actualPlant->idVegetable = 1 + x;

        return 1;
    }

    return 0;
}

extern void menuNotReady_Garden(Data* data) {
    if (data->lobby->askAction == SLEEP) {
        data->lobby->actualPlant = NULL;
        data->lobby->actionProcess = NONE;
    }
}

extern void DayPass(Data* data){
    for(int i = 0; i < 4; i++) {
        data->lobby->actualPlant = assignPlant(i, data->field);
        if (data->lobby->actualPlant->dayLeft > 0) {
            data->lobby->actualPlant->dayLeft--;
        }
    }
}
