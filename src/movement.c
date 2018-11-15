#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "movement.h"

extern void MovePlayer(Data* data)
{
    ProcessVelocity(&(data->Isaac->movement->velocity->x));
    ProcessVelocity(&(data->Isaac->movement->velocity->y));

    CheckObstacle(data);



    data->Isaac->pos->x+= (data->Isaac->movement->velocity->x)*1;
    data->Isaac->pos->y+= (data->Isaac->movement->velocity->y)*1;

    extern void ProcessAnimation(data->Isaac->movement)
}

extern void ProcessVelocity(int* v)
{
    if((*v)>0)
        (*v)-=1;
    else if((*v)<0)
        (*v)+=1;

    if((*v)>3)
        (*v)=3;
    else if((*v)<-3)
        (*v)=-3;
}



extern void CheckObstacle(Data* data)
{
    /*
    if(data->Isaac->movement->velocity->x || data->Isaac->movement->velocity->y)
    {
        if( data->TILE_ARRAY[ (data->Isaac->movement->pos->x + data->Isaac->movement->velocity->x)/XTILES , data->Isaac->movement->pos->y/YTILES ]->TYPE==WALL || (data->Isaac->movement->pos->x + data->Isaac->movement->velocity->x)<0 || (data->Isaac->movement->pos->x + data->Isaac->velocity->x)>1216)
            data->Isaac->velocity->x=0;
        if( data->TILE_ARRAY[ data->Isaac->movement->pos->x/XTILES , (data->Isaac->movement->pos->y + data->Isaac->movement->velocity->y)/YTILES ]->TYPE==WALL || (data->Isaac->movement->pos->y + data->Isaac->movement->velocity->y)<0 || (data->Isaac->movement->pos->y + data->Isaac->movement->velocity->y)>952)
            data->Isaac->movement->velocity->y=0;
    }
            ALL THIS IS TO DETECT COLLISIONS
            NEEDS TO BE EDITED TO TAKE CHARACTER WIDTH AND HEIGHT INTO ACCOUNT

    */


}

extern void ProcessAnimation(MovementValues * move)
{
    if(move->velocity->x || move->velocity->y )
        move->AnimationStep=(move->AnimationStep+1)%12;
    else
        move->AnimationStep=1;
}
