#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "data.h"
#include "movement.h"

extern void MovePlayer(Data* data)
{
    int tick=SDL_GetTicks();
    int timechange=tick - data->Isaac->movement->timesince;
    data->Isaac->movement->timesince=tick;
    if(timechange>300)
        timechange=0;

    ProcessVelocity(&(data->Isaac->movement->velocity->x),timechange);
    ProcessVelocity(&(data->Isaac->movement->velocity->y),timechange);
    //CheckObstacle(data);

    data->Isaac->movement->pos->x+= (data->Isaac->movement->velocity->x)*timechange/17/2;
    data->Isaac->movement->pos->y+= (data->Isaac->movement->velocity->y)*timechange/17/2;

    ProcessAnimation(data->Isaac->movement);

    SpriteSelection(data->Isaac->movement, data->Isaac->movement->SpriteBox);
}

extern void ProcessVelocity(int* v,int t)
{
    if((*v)>0)
    {
        (*v)-=1;
    }


    else if((*v)<0)
    {
        (*v)+=1;
    }


    if((*v)>12)
        (*v)=12;
    else if((*v)<-12)
        (*v)=-12;
}



extern void CheckObstacle(Data* data)
{
    int Xpos=data->Isaac->movement->pos->x;
    int Ypos=data->Isaac->movement->pos->y;

    int  Vx=(data->Isaac->movement->velocity->x);
    int  Vy=(data->Isaac->movement->velocity->y);

    int top=Ypos+85;
    int bot=Ypos+120;

    int left=Xpos+10;
    int right=Xpos+54;

    Tiles ** map=data->lobby->layout->map;

    if(Vx || Vy)
    {
        //printf("Xpos:%d Ypos:%d \n",Xpos,Ypos)
        if(Xpos + Vx<0 || Xpos + Vx>1216)
        {
            data->Isaac->movement->velocity->x=0;
        }
        if((Ypos + Vy)<-64 || (Ypos + Vy)>592)
        {
            data->Isaac->movement->velocity->y=0;
        }


        if(map[top/64][(Vx+left)/64].type=='W' || map[top/64][(Vx+right)/64].type=='W' || map[bot/64][(Vx+left)/64].type=='W' || map[bot/64][(Vx+right)/64].type=='W')
            data->Isaac->movement->velocity->x=0;
        if(map[(Vy+top)/64][left/64].type=='W' || map[(Vy+bot)/64][left/64].type=='W' || map[(Vy+top)/64][right/64].type=='W' || map[(Vy+bot)/64][(right)/64].type=='W')
            data->Isaac->movement->velocity->y=0;
    }


    Vx=(data->Isaac->movement->velocity->x);
    Vy=(data->Isaac->movement->velocity->y);

    if(Vx!=0 && Vy!=0)
    {
        if(map[(Vy+top)/64][(Vx+left)/64].type=='W' || map[(Vy+top)/64][(Vx+right)/64].type=='W' || map[(Vy+bot)/64][(Vx+left)/64].type=='W' || map[(Vy+bot)/64][(Vx+right)/64].type=='W')
        {
                printf(" YEEEEEEEEEEEEEEEEET");
                data->Isaac->movement->velocity->x=0;
                data->Isaac->movement->velocity->y=0;
        }
    }

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

