#include <stdlib.h>
#include <stdio.h>

#include "garden.h"

#include "engine/save.h"
#include "plants.h"
// StopVelocity(data->Isaac->movement); for benoit <3
static void test_plant(Data* data);

extern void doAction_Garden(Data* data) {
    data->lobby->askAction = 0;

    switch (checkAction_Garden(data)) {
        case 0: {
            data->lobby->actionProcess = INVENTORY;
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
            break;
        }
        default: {
            break;
        }
    }
}

extern int checkAction_Garden(Data* data) {
    if (data->lobby->layout->map[(int) ((data->Isaac->movement->pos->y)/64)+2][(int) ((data->Isaac->movement->pos->x)/64)].type == 'M') {
        return 1;
    }

    if (data->lobby->layout->map[((int) (data->Isaac->movement->pos->y)/64)+2][(int) (data->Isaac->movement->pos->x)/64].type == 'P') {
        return 2;
    }

    if (data->lobby->layout->map[(int) (data->Isaac->movement->pos->y)/64][(int) (data->Isaac->movement->pos->x)/64].type == 'S') {
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
            printf("%d day",data->Isaac->day);
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
    if ((int) (data->Isaac->movement->pos->x)/64 == 15 ) {
        if ((int) (data->Isaac->movement->pos->y) / 64 + 2 == 5) {
            data->lobby->actualPlant = data->field->plantBotLeft;
            // printf("%d %d %d %d ",data->lobby->actualPlant->dayLeft,data->lobby->actualPlant->vegetable,data->lobby->actualPlant->x,data->lobby->actualPlant->y );
        } else if ((int) (data->Isaac->movement->pos->y) / 64 + 2 == 2) {
            data->lobby->actualPlant = data->field->plantTopLeft;
        }
    } else if ((int) (data->Isaac->movement->pos->x) / 64 == 17) {
        if ((int) (data->Isaac->movement->pos->y) / 64 + 2 == 5) {
            data->lobby->actualPlant = data->field->plantBotRight;
        }
        else if ((int) (data->Isaac->movement->pos->y) / 64 + 2 == 2) {
            data->lobby->actualPlant = data->field->plantTopRight;
        }
    } else {
        data->lobby->actualPlant = NULL;
    }
}

extern void processField_Garden(Data* data) {
    // printf("%d %d %d %d ",data->lobby->actualPlant->dayLeft,data->lobby->actualPlant->vegetable,data->lobby->actualPlant->x,data->lobby->actualPlant->y );

    if (data->lobby->actualPlant->vegetable == 0) {
        data->lobby->actionProcess = PLANT; // plant ?
    } else if (data->lobby->actualPlant->dayLeft == 0) {
        data->lobby->actionProcess = GOTO_DUNGEON; //go to dj?
    } else if (data->lobby->actualPlant->dayLeft != 0) {
        data->lobby->actionProcess = WAIT;
    }
}

extern void menuSelectionDonjon_Garden(Data* data) {
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
        if (data->lobby->askMove == 0) {
            data->lobby->actualPlant->vegetable = 1;
            data->lobby->actualPlant->dayLeft = 3;

            // printf("%d %d %d %d ",data->lobby->actualPlant->dayLeft,data->lobby->actualPlant->vegetable,data->lobby->actualPlant->x,data->lobby->actualPlant->y );
        } else if (data->lobby->askMove == 1) {
            data->lobby->actualPlant->dayLeft = 3;
            data->lobby->actualPlant->vegetable = 2;
        } else if(data->lobby->askMove == 2) {
            data->lobby->actualPlant->dayLeft = 3;
            data->lobby->actualPlant->vegetable = 3 ;
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
