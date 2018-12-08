#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <SDL/SDL.h>

#include "../data.h"
#include "combat.h"
//#include "movement.h"
#include "monsters.h"
#include "../../utils/math.h"
#include "movement.h"


extern void ProcessMonsters(Player * Isaac,MonsterLList * monsters)
{

    (*monsters)=KillMonsters(*monsters);


    MonsterLList cur=(*monsters);

    while(cur)
    {
        switch(cur->monster->type)
        {
            case 0: //moth
                MothAI(cur->monster,Isaac);
                break;
            default:
                break;
        }
        cur=cur->next;
    }
}

extern void MothAI(Monster * moth, Player * Isaac)
{
    int timechange=lap_Timer(moth->movement->timesince);     // Timer to get the time since the last frame of movement
    if(timechange>300 || timechange<-300)
        timechange=0;

    double Xdistance= Isaac->movement->pos->x  - 32 - moth->movement->pos->x;
    double Ydistance= Isaac->movement->pos->y - moth->movement->pos->y;

    //oh shit here we go some fuckin trig
    double angle;
    if(Xdistance!=0)
    {
        angle=atan(Ydistance / Xdistance);
    }
    else angle=0;

    double dist= fabs(Xdistance) / fabs(cos(angle)) ;
    if(dist < 400 && !moth->AttackTimer->started)
    {
        moth->movement->velocity->x += fabs(cos(angle)) * sign(Xdistance) * timechange * 0.06;
        moth->movement->velocity->y += fabs(sin(angle)) * sign(Ydistance) * timechange * 0.06;

        if (moth->movement->velocity->x != 0) {
            angle = atanf(moth->movement->velocity->y / moth->movement->velocity->x);
        }

        ProcessVelocity(&(moth->movement->velocity->x), timechange, (4 * fabs(cos(angle))),0); //Dampens and caps velocity
        ProcessVelocity(&(moth->movement->velocity->y), timechange, (4 * fabs(sin(angle))), 0);

        moth->movement->pos->x+=(rand()%3)-1;
        moth->movement->pos->y+=(rand()%3)-1;

    }
    else if(moth->AttackTimer->started)
    {
        cap_Timer(moth->AttackTimer,500);

        if (moth->movement->velocity->x != 0) {
            angle = atanf(moth->movement->velocity->y / moth->movement->velocity->x);
        }

        ProcessVelocity(&(moth->movement->velocity->x), timechange, (4 * fabs(cos(angle))),0.05); //Dampens and caps velocity
        ProcessVelocity(&(moth->movement->velocity->y), timechange, (4 * fabs(sin(angle))), 0.05);

    }
    else
    {
        ProcessVelocity(&(moth->movement->velocity->x), timechange, (4 * fabs(cos(angle))),1); //Dampens and caps velocity
        ProcessVelocity(&(moth->movement->velocity->y), timechange, (4 * fabs(sin(angle))), 1);
    }


    moth->movement->pos->x+=moth->movement->velocity->x * timechange*0.06* moth->Speed; //TODO: make a PosChange function
    moth->movement->pos->y+=moth->movement->velocity->y * timechange*0.06* moth->Speed;



    moth->movement->Hitbox->x=moth->movement->pos->x+48;
    moth->movement->Hitbox->y=moth->movement->pos->y;


    MothAnimate(moth->movement,Xdistance,timechange);

    Damage(moth,Isaac,Xdistance,Ydistance);

}

extern void MothAnimate(MovementValues * movement,double Xdistance,int time)
{
    if(Xdistance>0)
    {
        movement->direction=1;
    }
    else
    {
        movement->direction=0;
    }
    movement->SpriteBox->y=movement->direction*96;
    if(!movement->velocity->x && !movement->velocity->y)
    {
        movement->SpriteBox->x=0;
    }
    else
    {
        movement->step= (movement->step+time)%200;
        movement->SpriteBox->x= ((movement->step/100)+1)*128 ;
    }
}


extern MonsterNode * KillMonsters(MonsterLList monsters)
{
    if(monsters==NULL) {
        return NULL;
    }
    else if(monsters->monster->Health<=0)
    {
        MonsterLList TempNext=monsters->next;
        //TODO add death cloud
        freemonster(monsters);

        return TempNext;
    }

    monsters->next=KillMonsters(monsters->next);

    return monsters;
}


extern void freemonster(MonsterLList  Node)
{
    freemovement(Node->monster->movement);
    free(Node->monster);
    free(Node);
}

extern void Damage(Monster * mob,Player * Isaac,int Xdistance,int Ydistance)
{
    if(BoxCollision(mob->movement->Hitbox,Isaac->movement->Hitbox))
    {
        Knockback(mob->movement->velocity,NULL,-1,Xdistance,Ydistance);
        if(Isaac->invulframes->started==false)
        {
            start_Timer(Isaac->invulframes);
            alterHealth(Isaac,mob->Damage,'c');
        }
    }
    if(BoxCollision(mob->movement->Hitbox,Isaac->combat->WeaponHitbox) && !mob->AttackTimer->started)
    {
        mob->Health-=1; //weapon->damage * Isaac->current_stats->Damage
        Knockback(mob->movement->velocity,mob->AttackTimer,Isaac->combat->direction,0,0);
    }
}

extern void Knockback(coordinates_entity* velocity,Timer * timer, int direction, int Xdistance, int Ydistance) {
    if(timer!=NULL) {
        start_Timer(timer);
    }
    if(direction==-1)
    {
        velocity->x=-Xdistance*10;
        velocity->y=-Ydistance*10 ;
    }
    else
    {
        switch (direction)
        {
            case 0:
                velocity->y=10;
                break;
            case 1:
                velocity->y=-10;
                break;
            case 2:
                velocity->x=10;
                break;
            case 3:
                velocity->x=-10;
                break;
            default:
                break;
        }
    }
}


