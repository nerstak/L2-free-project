#include "logic.h"
#include "../../engine/game/movement.h"
#include "../../engine/game/garden.h"
#include "../../engine/game/combat.h"

static void processTimer(Engine* engine, Data* data);

extern void logicProcess_Scene_lobby(Engine* engine, Data* data) {
    if(data->lobby->actionProcess == NONE){
        if(data->lobby->askAction == SELECT ){
            doAction_Garden(data);
        }else if (data->lobby->askAction == INVENTORY) {
            data->lobby->actionProcess = INVENTORY;
        }else {
            if(data->lobby->askCombat!=-1)
            {
                ProcessCombat(data,&(data->lobby->askCombat));
            }
            else
            {
                data->Isaac->combat->weaponHitBox->x=10000; // clean fix
                data->Isaac->combat->weaponHitBox->y=10000;
                data->Isaac->combat->weaponHitBox->h=0;
                data->Isaac->combat->weaponHitBox->w=0;
            }

            movePlayer_Movement(data, data->lobby->layout->map);
        }
    } else {
        stopVelocity_Movement(data->Isaac->movement);

        if(data->lobby->actionProcess == SLEEP){
            processSleep(data);
        }else if(data->lobby->actionProcess == GARDEN){
            processGarden(data);
        }else if(data->lobby->actionProcess == PLANT){
            menuSelectionPlanting_Garden(data);
        }else if(data->lobby->actionProcess == WAIT || data->lobby->actionProcess == NOT_ENOUGH) {
            processTimer(engine, data);
        }else if(data->lobby->actionProcess == SHOP) {
            data->lobby->actionProcess = NONE;
            display_SceneCollector(engine, data, "shop");
        }else if(data->lobby->actionProcess == PAUSE) {
            data->lobby->actionProcess = NONE;
            display_SceneCollector(engine, data, "pauseMenu");
        } else if(data->lobby->actionProcess == INVENTORY) {
            data->lobby->actionProcess = NONE;
            display_SceneCollector(engine, data, "inventory");
        }else if(data->lobby->actionProcess == GOTO_DUNGEON){
            menuSelectionDungeon_Garden(engine, data);
        }

        // We shall not reset if we switched to another scene, therefore free'd lobby structure
        if (data->lobby != NULL) {
            data->lobby->askAction = NONE;
        }
    }
}

static void processTimer(Engine* engine, Data* data) {
    if(isStarted_Timer(data->lobby->timerMessage)) {
        if(getTime_Timer(data->lobby->timerMessage) > 2) {
            stop_Timer(data->lobby->timerMessage);
            if(data->lobby->actionProcess == NOT_ENOUGH) {
                data->lobby->actionProcess = PLANT;
            } else {
                data->lobby->actionProcess = NONE;
            }
        }
    }
}