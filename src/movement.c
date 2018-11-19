#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "data.h"
#include "movement.h"

extern void MovePlayer(Data* data)
{
    ProcessVelocity(&(data->Isaac->movement->velocity->x));
    ProcessVelocity(&(data->Isaac->movement->velocity->y));
    CheckObstacle(data);

    data->Isaac->movement->pos->x+= (data->Isaac->movement->velocity->x)/2;
    data->Isaac->movement->pos->y+= (data->Isaac->movement->velocity->y)/2;

    ProcessAnimation(data->Isaac->movement);

    SpriteSelection(data->Isaac->movement, data->Isaac->movement->SpriteBox);

}

extern void ProcessVelocity(int* v)
{
    if((*v)>0)
        (*v)-=1;
    else if((*v)<0)
        (*v)+=1;

    if((*v)>12)
        (*v)=12;
    else if((*v)<-12)
        (*v)=-12;
}



extern void CheckObstacle(Data* data)
{
    if(data->Isaac->movement->velocity->x || data->Isaac->movement->velocity->y)
    {
        if((data->Isaac->movement->pos->x + data->Isaac->movement->velocity->x)<0 || (data->Isaac->movement->pos->x + data->Isaac->movement->velocity->x)>1216)
        {
            data->Isaac->movement->velocity->x=0;
        }
        if((data->Isaac->movement->pos->y + data->Isaac->movement->velocity->y)<-64 || (data->Isaac->movement->pos->y + data->Isaac->movement->velocity->y)>592)
        {
            data->Isaac->movement->velocity->y=0;
        }
    }


    if(data->lobby->layout->map[(data->Isaac->movement->pos->y+85)/64][(data->Isaac->movement->velocity->x+data->Isaac->movement->pos->x+10)/64].type=='W' || data->lobby->layout->map[(data->Isaac->movement->pos->y+85)/64][(data->Isaac->movement->velocity->x+data->Isaac->movement->pos->x+54)/64].type=='W' || data->lobby->layout->map[(data->Isaac->movement->pos->y+120)/64][(data->Isaac->movement->velocity->x+data->Isaac->movement->pos->x+10)/64].type=='W' || data->lobby->layout->map[(data->Isaac->movement->pos->y+120)/64][(data->Isaac->movement->velocity->x+data->Isaac->movement->pos->x+54)/64].type=='W')
        data->Isaac->movement->velocity->x=0;

    if(data->lobby->layout->map[(data->Isaac->movement->velocity->y+data->Isaac->movement->pos->y+85)/64][(data->Isaac->movement->pos->x+10)/64].type=='W' || data->lobby->layout->map[(data->Isaac->movement->velocity->y+data->Isaac->movement->pos->y+120)/64][(data->Isaac->movement->pos->x+10)/64].type=='W' || data->lobby->layout->map[(data->Isaac->movement->velocity->y+data->Isaac->movement->pos->y+85)/64][(data->Isaac->movement->pos->x+54)/64].type=='W' || data->lobby->layout->map[(data->Isaac->movement->velocity->y+data->Isaac->movement->pos->y+120)/64][(data->Isaac->movement->pos->x+54)/64].type=='W')
        data->Isaac->movement->velocity->y=0;



}

extern void ProcessAnimation(MovementValues * move)
{
    if(move->velocity->x || move->velocity->y )
        move->step=(move->step+1)%48;
    else
        move->step=0;

    if(move->velocity->y > 0 && move->velocity->y >= move->velocity->x && -move->velocity->y <= move->velocity->x) //DOWN 0
        move->direction=0;
    else if(move->velocity->y < 0 && move->velocity->y <= move->velocity->x && -move->velocity->y >= move->velocity->x) // UP 1
        move->direction=1;
    else if(move->velocity->x > 0) //RIGHT 2
        move->direction=2;
    else if(move->velocity->x < 0) //LEFT 3
        move->direction=3;

}

extern void SpriteSelection(MovementValues * move, SDL_Rect * box)
{
    box->x=(move->step/12)*64;
    box->y=move->direction*128;
//    box->h=128;
//    box->w=64;
}

