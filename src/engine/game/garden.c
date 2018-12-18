#include <stdlib.h>
#include <stdio.h>

#include "garden.h"

#include "inventory.h"
#include "../main.h"
#include "../timer.h"
#include "../save.h"
#include "plants.h"

static void findPlant(Data* data);
static int processPlanting(Data* data);
static void processField_Garden(Data* data);

extern void doAction_Garden(Data* data) {
    data->lobby->askAction = NONE;

    switch (checkAction_Garden(data)) {
        case 1: {
            data->lobby->actionProcess = SLEEP;
            break;
        }
        case 2: {
            data->lobby->actionProcess = GARDEN;
            break;
        }
        case 3: {
            data->lobby->actionProcess = SHOP;
            break;
        }
        default: {
            break;
        }
    }
}

extern int checkAction_Garden(Data* data) {
    if (checkTilesPlayer_Layout(data->Isaac, data->lobby->layout, 'M', 48, 0, 0, NULL, NULL)) {
        //Case for home
        return 1;
    }

    if (checkTilesPlayer_Layout(data->Isaac, data->lobby->layout, 'P', 30, 0, 0, NULL, NULL)) {
        //Case for plant spot
        return 2;
    }

    if (checkTilesPlayer_Layout(data->Isaac, data->lobby->layout, 'S', 48, 0, 0, NULL, NULL)) {
        //Case for shop
        return 3;
    }

    return 0;
}

extern void processSleep(Engine* engine, Data* data) {
    if(data->lobby->askAction == LEFT && data->lobby->cursor == 1) {
        data->lobby->cursor = 0;
        playEffect(engine->soundCollector, "lobby/move_button", 0);
    } else if(data->lobby->askAction == RIGHT && data->lobby->cursor == 0) {
        data->lobby->cursor = 1;
        playEffect(engine->soundCollector, "lobby/move_button", 0);
    } else if(data->lobby->askAction == SELECT) {
        if(data->lobby->cursor == 0) {
            writeSave(data);
            DayPass(data);
            playEffect(engine->soundCollector, "lobby/new_day", 0);
        } else {
            playEffect(engine->soundCollector, "lobby/confirm_button", 0);
        }
        data->lobby->actionProcess = NONE;
        data->lobby->cursor = 0;
    } else if(data->lobby->askAction == PAUSE) {
        data->lobby->actionProcess = NONE;
        data->lobby->cursor = 0;
    }
}

extern void processGarden(Data* data) {
    findPlant(data);
    processField_Garden(data);
}

static void findPlant(Data* data) {
    int coordX, coordY;
    if (checkTilesPlayer_Layout(data->Isaac, data->lobby->layout, 'P', 30, 0, 0, &coordX, &coordY)) {
        data->lobby->actualPlant = assignNumberPlant_Coord(coordX, coordY, data, NULL);
    } else {
        data->lobby->actualPlant = NULL;
    }
}

static void processField_Garden(Data* data) {
    if(data->lobby->actualPlant != NULL) {
        if (data->lobby->actualPlant->idVegetable == -1) {
            //Zone is empty
            data->lobby->actionProcess = PLANT;
        } else if (data->lobby->actualPlant->dayLeft == 0) {
            //Vegetable has matured
            data->lobby->actionProcess = GOTO_DUNGEON;
        } else if (data->lobby->actualPlant->dayLeft != 0) {
            //Vegetable is still growing
            data->lobby->actionProcess = WAIT;
            start_Timer(data->lobby->timerMessage);
        }
    }
}

extern void menuSelectionDungeon_Garden(Engine* engine, Data* data) {
    if (data->lobby->askAction == LEFT && data->lobby->cursor == 1) {
        data->lobby->cursor = 0;
        playEffect(engine->soundCollector, "lobby/move_button",0 );
    } else if (data->lobby->askAction == RIGHT && data->lobby->cursor == 0) {
        data->lobby->cursor = 1;
        playEffect(engine->soundCollector, "lobby/move_button", 0);
    }
    else if (data->lobby->askAction == SELECT) {
        data->lobby->actionProcess = NONE;
        if(data->lobby->cursor == 1 || data->Isaac->gameStats->dungeonDay == 1) {
            playEffect(engine->soundCollector, "lobby/confirm_button", 0);
            data->lobby->cursor = 0;
            data->lobby->actualPlant = NULL;
        } else if (data->lobby->cursor == 0) {
            playEffect(engine->soundCollector, "loading/entering_dungeon", 0);
            data->field->currentPlant = data->lobby->actualPlant;
            data->Isaac->gameStats->dungeonDay = 1;
            data->lobby->cursor = 0;
            display_SceneCollector(engine, data, "dungeon");
        }
    }  else if(data->lobby->askAction == PAUSE) {
        data->lobby->actionProcess = NONE;
        data->lobby->cursor = 0;
    }
}

extern void menuSelectionPlanting_Garden(Engine* engine, Data* data) {
    if(data->lobby->askAction == LEFT && data->lobby->cursor > 0) {
        data->lobby->cursor--;
        playEffect(engine->soundCollector, "lobby/move_button", 0);
    }else if(data->lobby->askAction == RIGHT && data->lobby->cursor < 5) {
        data->lobby->cursor++;
        playEffect(engine->soundCollector, "lobby/move_button", 0);
    }else if(data->lobby->askAction == SELECT) {
        if(data->lobby->cursor == 5) {
            data->lobby->cursor = 0;
            data->lobby->actualPlant = NULL;
            data->lobby->actionProcess = NONE;
            playEffect(engine->soundCollector, "loading/leave_menu", 0);
        } else {
            if(processPlanting(data) == 1) {
                data->lobby->cursor = 0;
                data->lobby->actualPlant = NULL;
                data->lobby->actionProcess = NONE;
                playEffect(engine->soundCollector, "player/plant", 0);
            } else {
                data->lobby->actionProcess = NOT_ENOUGH;
                start_Timer(data->lobby->timerMessage);
                playEffect(engine->soundCollector, "lobby/confirm_button", 0);
            }
        }
    } else if(data->lobby->askAction == PAUSE) {
        data->lobby->actionProcess = NONE;
        data->lobby->cursor = 0;
    }
}

static int processPlanting(Data* data) {
    SlotInventory* plant = search_SlotInventory(data->Isaac->inventory, data->lobby->cursor);

    if(plant){
        //Note that the remaining days are stored in the health
        data->lobby->actualPlant->dayLeft = (int) plant->characteristics->health;
        data->lobby->actualPlant->idVegetable = plant->id;
        plant->quantity--;
        if(plant->quantity <= 0) {
            remove_SlotInventory(&(data->Isaac->inventory),plant->id,&(data->Isaac->sizeInventory));
        }
        return 1;
    }
    return 0;
}

extern void DayPass(Data* data){
    for(int i = 0; i < 4; i++) {
        data->lobby->actualPlant = assignPlant(i, data->field);
        if (data->lobby->actualPlant->dayLeft > 0) {
            data->lobby->actualPlant->dayLeft--;
        }
    }
}
