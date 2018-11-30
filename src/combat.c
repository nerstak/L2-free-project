#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "data.h"
#include "combat.h"

extern void ProcessCombat(Data * data, int direction)
{
    data->Isaac->combat->direction=direction;
    if(data->Isaac->combat->step==0)
    {
        data->Isaac->combat->timesince=SDL_GetTicks();     // Timer to get the time since the last frame of movement
        data->Isaac->combat->step++;
    }

    CombatAnimation(data->Isaac->combat,SDL_GetTicks() - data->Isaac->combat->timesince);

    CombatSprite(data->Isaac->combat);
}


extern void CombatAnimation(CombatValues * combat,int time)
{
    combat->step+=time/4;
}


extern void CombatSprite(CombatValues * combat)
{
    int xSelect,ySelect;
    ySelect=combat->direction;
    xSelect=(combat->step-100) / 200;
    if(xSelect<0)
        xSelect=0;
    if(xSelect>3)
        xSelect=3;

    combat->SpriteBox->x=xSelect*192; //x*3*64
    combat->SpriteBox->y=ySelect*192;
    combat->SpriteBox->h=combat->SpriteBox->w=192;
}
