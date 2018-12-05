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
                Damage(cur->monster,Isaac);
                break;
            default:
                break;
        }
        cur=cur->next;
    }
}

extern void MothAI(Monster * moth, Player * Isaac)
{
    // TODO: convert all my shitty timers to clem's clean ones
    int tick=SDL_GetTicks();
    int timechange=tick - moth->movement->timesince;     // Timer to get the time since the last frame of movement
    moth->movement->timesince=tick;
    if(timechange>300 || timechange<-300)
        timechange=0;

    double Xdistance= Isaac->movement->pos->x  - 64 - moth->movement->pos->x;
    double Ydistance= Isaac->movement->pos->y + 32 - moth->movement->pos->y;

    //oh shit here we go some fuckin trig
    double angle;
    if(Xdistance!=0)
    {
        angle=atan(Ydistance / Xdistance);
    }
    else angle=0;

    int xSign=sign(Xdistance);

    moth->movement->velocity->x+=  fabs(cos(angle)) * sign(Xdistance) * timechange * 0.06;
    moth->movement->velocity->y+=  fabs(sin(angle)) * sign(Ydistance) * timechange * 0.06;

    if(moth->movement->velocity->x!=0)
    {
        angle = atan(moth->movement->velocity->y / moth->movement->velocity->x);
    }
    else angle=0;

    ProcessVelocity(&(moth->movement->velocity->x), timechange, (4 * fabs(cos(angle))) ,0); //Dampens and caps velocity
    ProcessVelocity(&(moth->movement->velocity->y), timechange, (4 * fabs(sin(angle))), 0);

    moth->movement->pos->x+=moth->movement->velocity->x * timechange*0.06* moth->Speed; //TODO: make a PosChange function
    moth->movement->pos->y+=moth->movement->velocity->y * timechange*0.06* moth->Speed;

    moth->movement->Hitbox->x=moth->movement->pos->x+64;
    moth->movement->Hitbox->y=moth->movement->pos->y;



}


extern MonsterNode * KillMonsters(MonsterLList monsters)
{
    if(monsters==NULL) {
        return NULL;
    }
    else if(monsters->monster->Health<=0)
    {
        MonsterLList TempNext=monsters->next;

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

extern void Damage(Monster * mob,Player * Isaac)
{
    if(BoxCollision(mob->movement->Hitbox,Isaac->movement->Hitbox))
    {
        Isaac->stats->current->health-=1;
    }
    if(BoxCollision(mob->movement->Hitbox,Isaac->combat->WeaponHitbox))
    {
        mob->Health-=1; //weapon->damage * Isaac->current_stats->Damage
    }

}
