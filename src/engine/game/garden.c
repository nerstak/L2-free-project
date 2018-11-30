#include <stdlib.h>
#include <stdio.h>

#include "garden.h"

#include "../save.h"
#include "plants.h"

static void test_plant(Data* data);

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
    if(checkTilesPlayer(data->Isaac, data->lobby->layout, 'M', 48, 0, 0, NULL, NULL)) {
        //Case for home
        return 1;
    }

    if(checkTilesPlayer(data->Isaac, data->lobby->layout, 'P', 30, 0, 0, NULL, NULL)) {
        //Case for plant spot
        return 2;
    }

    if(checkTilesPlayer(data->Isaac, data->lobby->layout, 'S', 48, 0, 0, NULL, NULL)) {
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
    if(checkTilesPlayer(data->Isaac, data->lobby->layout, 'P', 30, 0, 0, &coordX, &coordY)) {
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
        // printf("%d",data->lobby->askMove);
        if (data->lobby->askMove > 3) {
            data->lobby->askMove = 3;
        }

        if (data->lobby->askMove < 0) {
            data->lobby->askMove = 0;
        }
    } else if (data->lobby->askAction == 1) {
        //TODO: Adapt the ID of vegetables, and check inside the inventory
        if (data->lobby->askMove == 0) {
            data->lobby->actualPlant->idVegetable = 1;
            data->lobby->actualPlant->dayLeft = 3;

            // printf("%d %d %d %d ",data->lobby->actualPlant->dayLeft,data->lobby->actualPlant->idVegetable,data->lobby->actualPlant->x,data->lobby->actualPlant->y );
        } else if (data->lobby->askMove == 1) {
            data->lobby->actualPlant->dayLeft = 3;
            data->lobby->actualPlant->idVegetable = 2;
        } else if(data->lobby->askMove == 2) {
            data->lobby->actualPlant->dayLeft = 3;
            data->lobby->actualPlant->idVegetable = 3 ;
        } else if(data->lobby->askMove == 3) {

        }

        data->lobby->actualPlant = NULL;
        data->lobby->actionProcess = NONE;
    }
}

extern void menuNotReady_Garden(Data* data) {
    if (data->lobby->askAction == 1) {
        data->lobby->actualPlant = NULL;
        data->lobby->actionProcess = NONE;
    }
}

