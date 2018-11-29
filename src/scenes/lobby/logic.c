#include "logic.h"
#include "../../movement.h"
#include "../../garden.h"

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
            StopVelocity(data->Isaac->movement);
            doAction_Garden(data);
        }
        else {
            MovePlayer(data, data->lobby->layout->map);
        }
    } else {
        StopVelocity(data->Isaac->movement);
        if(data->lobby->actionProcess == SLEEP){
            processMenu1_Garden(data);
        }
        else if(data->lobby->actionProcess == GARDEN){
            processMenu2_Garden(data);
        }
        else if(data->lobby->actionProcess == PLANT){
            menuSelectionPlanting_Garden(data);
        }
        else if(data->lobby->actionProcess == GOTO_DUNGEON){
            menuSelectionDungeon_Garden(data);
        }
        else if(data->lobby->actionProcess == WAIT){
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

        if (data->lobby->actionProcess == 10) {
            data->lobby->actionProcess = NONE;
            display_SceneCollector(engine, data, "dungeon");
        }
    }
}
