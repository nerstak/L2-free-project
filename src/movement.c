#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "data.h"
#include "movement.h"

extern void MovePlayer(Data* data)
{
    int tick=SDL_GetTicks();
    int timechange=tick - data->Isaac->movement->timesince;     // Timer to get the time since the last frame of movement
    data->Isaac->movement->timesince=tick;
    if(timechange>300)
        timechange=0;


    ProcessVelocity(&(data->Isaac->movement->velocity->x),timechange); //Dampens and caps velocity
    ProcessVelocity(&(data->Isaac->movement->velocity->y),timechange);
    CheckObstacle(data,timechange); //Checks for obstacles on the map and adjusts velocity accordingly

    data->Isaac->movement->pos->x += (data->Isaac->movement->velocity->x)*timechange*0.03; //actually changes the character's movement according to the velocity we done got
    data->Isaac->movement->pos->y += (data->Isaac->movement->velocity->y)*timechange*0.03; //timechange*0.03 is equal to 0.5 at 60fps which, since max V is 12,means it moves 6 pixels a frame at 60 fps

    ProcessAnimation(data->Isaac->movement,timechange);// takes care of the character's animation

    SpriteSelection(data->Isaac->movement, data->Isaac->movement->SpriteBox); //selects the appropriate section of the spritesheet to display
}

extern void ProcessVelocity(float* v,int t)
{
    if((*v)>0) // gradually slows down the player so he stops when not pressing the button
    {
        (*v)-=t*0.06; //this is equal to 1 at 60 fps. This allows the acceleration to be equal to the deceleration
        if((*v)<0)
            (*v)=0;
    }


    else if((*v)<0)
    {
        (*v)+=t*0.06;
        if((*v)>0)
            (*v)=0;
    }


    if((*v)>12) // Caps velocity
        (*v)=12;
    else if((*v)<-12)
        (*v)=-12;
}



extern void CheckObstacle(Data* data,int t)
{
    float Xpos=data->Isaac->movement->pos->x; //X and Y coordinates of the top left of the player
    float Ypos=data->Isaac->movement->pos->y;

    float  Vx=(data->Isaac->movement->velocity->x)*t*0.03; // this is the total change in position due to velocity
    float  Vy=(data->Isaac->movement->velocity->y)*t*0.03;

    int top=(Ypos + 85)/64; //these 4 are the top bottom left and right values for the walls of the hitbox
    int bot=(Ypos + 120)/64;
    int left=(Xpos + 10)/64;
    int right=(Xpos + 54)/64;

    int RightHit=(Vx + Xpos + 54)/64; //these are the layout-relative-coordinates of each side of the hitbox after they have moved from velocity
    int LeftHit=(Vx + Xpos + 10)/64;
    int TopHit=(Vy + Ypos + 85)/64;
    int BotHit=(Vy + Ypos + 120)/64;

    Tiles ** map=data->lobby->layout->map; // getting 2d array layout of map

    if(Vx!=0 || Vy!=0)
    {
        if(Xpos + Vx<0 || Xpos + Vx>1216) //if the player is going to move out of bounds stop his velocity
        {
            data->Isaac->movement->velocity->x=0;
        }
        if((Ypos + Vy)<-64 || (Ypos + Vy)>592)
        {
            data->Isaac->movement->velocity->y=0;
        }
    }

    Vx=(data->Isaac->movement->velocity->x);
    Vy=(data->Isaac->movement->velocity->y);

    if(Vx!=0 || Vy!=0)
    {
        //If one of the player's four corners is inside a wall after moving on an axis, it cancels movement.
        if(map[top][LeftHit].type=='W' || map[top][RightHit].type=='W' || map[bot][LeftHit].type=='W' || map[bot][RightHit].type=='W')
            data->Isaac->movement->velocity->x=0;
        if(map[TopHit][left].type=='W' || map[BotHit][left].type=='W' || map[TopHit][right].type=='W' || map[BotHit][right].type=='W')
            data->Isaac->movement->velocity->y=0;
    }


    Vx=(data->Isaac->movement->velocity->x);
    Vy=(data->Isaac->movement->velocity->y);

    if(Vx!=0 && Vy!=0)
    {
        //if the player moves towards a corner at a perfect angle, there wont be anything to block movement iin both cardinal directions and we should hence check diagonals.
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
        move->step=(move->step+(10*t/17))%480; //bases how much you advance in the animation on time change
    else
        move->step=0; //resets animation when player stops moving


    //the direction of the player is based on the direction with the most velocity
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
    box->x=(move->step/120)*64; // 0 1 2 3 based on where we are in the animation times the width of a single sprite
    box->y=move->direction*128; // 0 1 2 3 based on direction times the width of a single sprite
//    box->h=128;
//    box->w=64;
}

