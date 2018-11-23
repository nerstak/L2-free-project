#include "logic.h"
#include "../../movement.h"

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


if(data->lobby->menuHouse == 0){


    if(data->lobby->askAction == 1 ){
        doAction(data);
    }
   else MovePlayer(data);
    }
else if(data->lobby->menuHouse == 1){
       processMenu1(data);
}
}
