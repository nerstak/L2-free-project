#include <stdlib.h>
#include <stdio.h>

#include "garden.h"

#include "../save.h"
#include "plants.h"

static void test_plant(Data* data);
static int ToPlant(int x, Data* data);

extern void doAction_Garden(Data* data) {
    data->lobby->askAction = 0;

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

extern void processMenu1_Garden(Data* data) {
    if (data->lobby->askAction == 0) {
        if (data->lobby->askMove > 1) {
            data->lobby->askMove = 1;
        }
        if (data->lobby->askMove < 0) {
            data->lobby->askMove = 0;
        }
    } else if (data->lobby->askAction == 1) {
        if (data->lobby->askMove == 0) {
            writeSave(data);
            DayPass(data);
        }
        else {

        }

        data->lobby->askAction = 0;
        data->lobby->actionProcess = NONE;
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
    // printf("%d %d %d %d ",data->lobby->actualPlant->dayLeft,data->lobby->actualPlant->idVegetable,data->lobby->actualPlant->x,data->lobby->actualPlant->y );

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
    if (data->lobby->askAction == 0) {
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
    //printf(" day left : %d  Vege :%d",data->lobby->actualPlant->dayLeft,data->lobby->actualPlant->idVegetable);
}

static int ToPlant(int x, Data* data){
    SlotInventory * plant = search_SlotInventory(data->Isaac->inventory, x);
    int q = plant->quantity;

    if(q > 0){
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
    if (data->lobby->askAction == 1) {
        data->lobby->actualPlant = NULL;
        data->lobby->actionProcess = NONE;
    }
}

extern void DayPass(Data* data){
    for (int n = 1; n<5; n++) {
        switch(n) {
            case 1: {
                data->lobby->actualPlant = data->field->plantBotLeft;

                break;
            }
            case 2: {
                data->lobby->actualPlant = data->field->plantTopLeft;

                break;
            }
            case 3: {
                data->lobby->actualPlant = data->field->plantBotRight;

                break;
            }
            case 4: {
                data->lobby->actualPlant = data->field->plantTopRight;

                break;
            }
            default: {
                printf("Problème");
                exit(EXIT_FAILURE);

                break;
            }
        }

        if (data->lobby->actualPlant->idVegetable != 0) {
            if (data->lobby->actualPlant->dayLeft > 0) {
                data->lobby->actualPlant->dayLeft--;
            }
        }
    }
}
