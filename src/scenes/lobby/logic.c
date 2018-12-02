#include "logic.h"
#include "../../engine/game/movement.h"
#include "../../engine/game/garden.h"
#include "../../engine/game/combat.h"

extern void logicProcess_Scene_lobby(Engine* engine, Data* data)
{
    if(data->lobby->counterPressKey != 0){
         data->lobby->counterPressKey --;
    }
    if(data->lobby->counterPressKey == 1){
        data->lobby->askAction = 1;
    }
    else {
        data->lobby->askAction = 0;
    }

    if (data->lobby->counterPressKeyMove < 0){
        data->lobby->counterPressKeyMove ++;
    }
    else if(data->lobby->counterPressKeyMove > 0){
        data->lobby->counterPressKeyMove --;
    }
    if( data->lobby->counterPressKeyMove == 1){
        data->lobby->askMove ++;
    }
    else if ( data->lobby->counterPressKeyMove == -1 ){
        data->lobby->askMove --;
    }



    if(data->lobby->actionProcess == NONE){
        if(data->lobby->askAction == 1 ){
            doAction_Garden(data);
        } else {
            if(data->lobby->askCombat!=-1)
            {
                ProcessCombat(data,data->lobby->askCombat);
            }
            MovePlayer(data, data->lobby->layout->map);
        }
    } else {
        StopVelocity(data->Isaac->movement);
        if(data->lobby->actionProcess == SLEEP){
            processMenu1_Garden(data);
        }else if(data->lobby->actionProcess == GARDEN){
            processMenu2_Garden(data);
        }else if(data->lobby->actionProcess == PLANT){
            menuSelectionPlanting_Garden(data);
        }else if(data->lobby->actionProcess == GOTO_DUNGEON){
            menuSelectionDungeon_Garden(data);
        }else if(data->lobby->actionProcess == WAIT || data->lobby->actionProcess == NOT_ENOUGH){
            menuNotReady_Garden(data);
        }

        if(data->lobby->actionProcess == INVENTORY) {
            data->lobby->actionProcess = NONE;
            display_SceneCollector(engine, data, "inventory");
        }
        if(data->lobby->actionProcess == SHOP) {
            data->lobby->actionProcess = NONE;
            display_SceneCollector(engine, data, "shop");
        }
    }
}
