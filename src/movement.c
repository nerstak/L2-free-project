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
    CheckObstacle(data,timechange);

    data->Isaac->movement->pos->x += (data->Isaac->movement->velocity->x)*timechange*0.03;
    data->Isaac->movement->pos->y += (data->Isaac->movement->velocity->y)*timechange*0.03;

    ProcessAnimation(data->Isaac->movement,timechange);

    SpriteSelection(data->Isaac->movement, data->Isaac->movement->SpriteBox);
}

extern void ProcessVelocity(float* v,int t)
{
    if((*v)>0)
    {
        (*v)-=t*0.06;
        if((*v)<0)
            (*v)=0;
    }


    else if((*v)<0)
    {
        (*v)+=t*0.06;
        if((*v)>0)
            (*v)=0;
    }


    if((*v)>12)
        (*v)=12;
    else if((*v)<-12)
        (*v)=-12;
}



extern void CheckObstacle(Data* data,int t)
{
    float Xpos=data->Isaac->movement->pos->x;
    float Ypos=data->Isaac->movement->pos->y;

    float  Vx=(data->Isaac->movement->velocity->x)*t*0.03;
    float  Vy=(data->Isaac->movement->velocity->y)*t*0.03;

    int top=(Ypos + 85)/64;
    int bot=(Ypos + 120)/64;

    int left=(Xpos + 10)/64;
    int right=(Xpos + 54)/64;

    int RightHit=(Vx + Xpos + 54)/64;
    int LeftHit=(Vx + Xpos + 10)/64;
    int TopHit=(Vy + Ypos + 85)/64;
    int BotHit=(Vy + Ypos + 120)/64;

    Tiles ** map=data->lobby->layout->map;

    if(Vx!=0 || Vy!=0)
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


        if(map[top][LeftHit].type=='W' || map[top][RightHit].type=='W' || map[bot][LeftHit].type=='W' || map[bot][RightHit].type=='W')
            data->Isaac->movement->velocity->x=0;
        if(map[TopHit][left].type=='W' || map[BotHit][left].type=='W' || map[TopHit][right].type=='W' || map[BotHit][right].type=='W')
            data->Isaac->movement->velocity->y=0;
    }


    Vx=(data->Isaac->movement->velocity->x);
    Vy=(data->Isaac->movement->velocity->y);

    if(Vx!=0 && Vy!=0)
    {
        if(map[TopHit][LeftHit].type=='W' || map[TopHit][RightHit].type=='W' || map[BotHit][LeftHit].type=='W' || map[BotHit][RightHit].type=='W')
        {
                //printf(" YEEEEEEEEEEEEEEEEET");
                data->Isaac->movement->velocity->x=0;
                data->Isaac->movement->velocity->y=0;
        }
    }

}

extern void ProcessAnimation(MovementValues * move,int t)
{
    if(move->velocity->x || move->velocity->y )
        move->step=(move->step+(10*t/17))%480;
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
    box->x=(move->step/120)*64;
    box->y=move->direction*128;
//    box->h=128;
//    box->w=64;
}

