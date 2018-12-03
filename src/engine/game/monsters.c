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



extern void ProcessMonsters(Player * Isaac,MonsterLList * monsters)
{
    *monsters=KillMonsters(*monsters);


    MonsterLList cur=*monsters;

    while(!cur)
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
    // TODO: convert all my shitty timers to clem's clean ones
    int tick=SDL_GetTicks();
    int timechange=tick - moth->movement->timesince;     // Timer to get the time since the last frame of movement
    moth->movement->timesince=tick;
    if(timechange>300)
        timechange=0;

    double Xdistance= Isaac->movement->pos->x - moth->movement->pos->x;
    double Ydistance= Isaac->movement->pos->y - moth->movement->pos->y;

    //oh shit here we go some fuckin trig
    double angle=atan(Ydistance / Xdistance);

    moth->movement->velocity->x+=2 * abs(cos(angle)) * sign(Xdistance) * timechange * 0.06;
    moth->movement->velocity->y+=2 * abs(sin(angle)) * sign(Ydistance) * timechange * 0.06;

    ProcessVelocity(&(moth->movement->velocity->x),timechange,8,0.5); //Dampens and caps velocity
    ProcessVelocity(&(moth->movement->velocity->y),timechange,8,0.5);

    moth->movement->pos->x+=moth->movement->velocity->x * timechange*0.03* moth->Speed; //TODO: make a PosChange function
    moth->movement->pos->x+=moth->movement->velocity->y * timechange*0.03* moth->Speed;



}


extern MonsterNode * KillMonsters(MonsterLList monsters)
{
    if(monsters=NULL)
        return NULL;

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
