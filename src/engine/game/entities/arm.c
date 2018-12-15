#include <stdlib.h>

#include "arm.h"
#include "main.h"
#include "../../../utils/math.h"
#include "../movement.h"



extern void ai_EArm(Entity* e, Data* data,float maxhealth)
{
    int timeChange = lap_Timer(e->movement->timeSince);
    if(timeChange > 300 || timeChange<-300) {
        timeChange = 0;
    }


    e->movement->hitBox->x= (Sint16) (e->movement->position->x + 16 );
    e->movement->hitBox->y= (Sint16) (e->movement->position->y + 32);

    if(e->attackTimer->started) {
        cap_Timer(e->attackTimer,500);
    }
    /*
    else if(e->shootTimer->started){
        cap_Timer(e->shootTimer,2000);
    }
    else
    {
        Coordinate* source=malloc(sizeof(Coordinate));
        source->x=e->movement->position->x+48;
        source->y=e->movement->position->y+80 ;

        shoot_Projectile(data,source,5,e->damage,1300,e->type);
        lap_Timer(e->shootTimer);
    } */

    animate_EArm(e,timeChange,maxhealth);
    damage_Entity(e, data, 0, 0);

    if(e->health<=0)
    {
        EntityList* Deadarm=malloc(sizeof(EntityList));
        Deadarm->next=NULL;
        Deadarm->data=e;
        append_EntityNode(Deadarm,&(data->dyingEntities));
        e=NULL;
    }
}



extern void animate_EArm(Entity* e, int time,float maxhealth)
{
    int state=0;
    if(e->health<=maxhealth/2)
    {
        state=1;
    }
    //e->movement->spriteBox->x= (Sint16) ((int) (((maxhealth - e->health) / maxhealth) * 5) * 384);
    e->movement->spriteBox->x=  128 * ((2*e->movement->direction)+state);

    e->movement->animationStep = (e->movement->animationStep + time) % 1000;
    int step=abs( (e->movement->animationStep / 250) - 2);
    e->movement->spriteBox->y= (Sint16) (224 * step);
}
