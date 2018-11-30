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

    SetCombatHitbox(data->Isaac);


    //after this is temp
    SDL_Rect dummy;
    dummy.x=960;
    dummy.y=256;
    dummy.h=64;
    dummy.w=64;
    if(BoxCollision(&dummy,data->Isaac->combat->WeaponHitbox))
    {
        printf("\n           HIT\n");
    }


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
        case 0:
            Isaac->combat->WeaponHitbox->x = (Isaac->movement->pos->x + 64) - (step * 64) ;

            Isaac->combat->WeaponHitbox->y = Isaac->movement->pos->y + 96;
            break;
        case 1:
            Isaac->combat->WeaponHitbox->x = (Isaac->movement->pos->x - 64) + (step * 64) ;

            Isaac->combat->WeaponHitbox->y = Isaac->movement->pos->y - 32;
            break;
        case 2:
            Isaac->combat->WeaponHitbox->x = Isaac->movement->pos->x + 64;

            Isaac->combat->WeaponHitbox->y = (Isaac->movement->pos->y - 32) + (step * 64);
            break;
        case 3:
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

