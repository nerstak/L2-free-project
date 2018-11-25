#include "logic.h"
#include "../../movement.h"

extern void logicProcess_Scene_lobby(Engine* engine, Data* data)
{
    MovePlayer(data);
    //StopVelocity(data->Isaac->movement); // for benoit <3
}
