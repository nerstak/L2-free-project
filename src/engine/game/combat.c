#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "../data.h"
#include "combat.h"

extern void ProcessCombat(Data * data, int direction)
{
    data->Isaac->combat->direction=direction;
    if(data->Isaac->combat->step==0)
    {
        start_Timer(data->Isaac->combat->timesince);     // Timer to get the time since the last frame of movement
    }

    CombatAnimation(data->Isaac->combat,getTicks_Timer(data->Isaac->combat->timesince)+1,data->Isaac->stats->current->agility);

    CombatSprite(data->Isaac->combat);

    SetCombatHitbox(data->Isaac);



}


extern void CombatAnimation(CombatValues * combat,int time,int agility)
{
    combat->step=time*agility;
}


extern void CombatSprite(CombatValues * combat)
{
    int xSelect,ySelect;
    ySelect=combat->direction;
    xSelect=(combat->step) / 100;
    if(xSelect>3)
        xSelect=3;

    combat->SpriteBox->x=xSelect*192; //x*3*64
    combat->SpriteBox->y=ySelect*192;
    combat->SpriteBox->h=combat->SpriteBox->w=192;


}


extern void SetCombatHitbox(Player * Isaac)
{
    int step;
    // for scythe
    Isaac->combat->WeaponHitbox->h=64;
    Isaac->combat->WeaponHitbox->w=64;

    step=Isaac->combat->SpriteBox->x / 192;
    if(step>1)
        step--;

    switch(Isaac->combat->direction)
    {
        case 0: //down
            Isaac->combat->WeaponHitbox->x = (Isaac->movement->pos->x + 64) - (step * 64) ;

            Isaac->combat->WeaponHitbox->y = Isaac->movement->pos->y + 96;
            break;
        case 1: //up
            Isaac->combat->WeaponHitbox->x = (Isaac->movement->pos->x - 64) + (step * 64) ;

            Isaac->combat->WeaponHitbox->y = Isaac->movement->pos->y - 32;
            break;
        case 2: //right
            Isaac->combat->WeaponHitbox->x = Isaac->movement->pos->x + 64;

            Isaac->combat->WeaponHitbox->y = (Isaac->movement->pos->y - 32) + (step * 64);
            break;
        case 3: //left
            Isaac->combat->WeaponHitbox->x = Isaac->movement->pos->x - 64;

            Isaac->combat->WeaponHitbox->y = (Isaac->movement->pos->y - 32) + (step * 64);
            break;
        default:
            break;

    }
}


extern bool BoxCollision(SDL_Rect * box1, SDL_Rect * box2)
{
    if(CheckBox(box1->x,box1->y,box2) || CheckBox(box1->x + box1->w,box1->y,box2) ||
       CheckBox(box1->x,box1->y + box1->h,box2) || CheckBox(box1->x + box1->w,box1->y + box1->h,box2) ||

       CheckBox(box2->x,box2->y,box1) || CheckBox(box2->x + box2->w,box2->y,box1) ||
       CheckBox(box2->x,box2->y + box2->h,box1) || CheckBox(box2->x + box2->w,box2->y + box2->h,box1))
    {
        return true;
    }
    else
        return false;
}

extern bool CheckBox(int xPoint, int yPoint, SDL_Rect * boxtarget)
{
    if(
         (  (xPoint > boxtarget->x) && ( xPoint < (boxtarget->x + boxtarget->w) )  )
         &&
         (  (yPoint > boxtarget->y) && ( yPoint < (boxtarget->y + boxtarget->h) )  )
       )
        return true;
    else
        return false;
}

