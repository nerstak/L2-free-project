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


if(data->lobby->menuHouse == 0){
    if(data->lobby->askAction == 1 ){
        doAction_Garden(data);
    }
   else MovePlayer(data);
}
else if(data->lobby->menuHouse == 1){
    processMenu1_Garden(data);
}
else if(data->lobby->menuHouse == 2){
    processMenu2_Garden(data);
}
else if(data->lobby->menuHouse == 21){

    menuSelectionPlanting_Garden(data);
}
else if(data->lobby->menuHouse == 22){
    menuSelectionDonjon_Garden(data);
}
else if(data->lobby->menuHouse == 23){
    menuNotReady_Garden(data);
}





}
