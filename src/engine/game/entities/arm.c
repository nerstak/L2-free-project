#include <stdlib.h>
#include <math.h>

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

    if(isStarted_Timer(e->shootTimer))
    {
        punch(data, e, data->Isaac->movement->position, maxhealth, data->dungeonScene->currentRoom->layout->map);
    }

    e->movement->position->x+=e->movement->velocity->x * timeChange *0.06 * e->speed;
    e->movement->position->y+=e->movement->velocity->y * timeChange *0.06 * e->speed;

    float Vx=e->movement->velocity->x;
    float Vy=e->movement->velocity->y;

    animate_EArm(e,timeChange,maxhealth);
    damage_Entity(e, data, 0, 0);
    e->movement->velocity->x=Vx;
    e->movement->velocity->y=Vy;



    if(e->health<=0)
    {
        EntityList* Deadarm=malloc(sizeof(EntityList));
        Deadarm->next=NULL;
        Deadarm->data=e;
        Deadarm->data->movement->animationStep=0;
        append_EntityNode(Deadarm,&(data->dyingEntities));
        e=NULL;
    }
}



extern void animate_EArm(Entity* e, int time,float maxhealth)
{
    int state=0,step;
    if(e->health<=maxhealth/2)
    {
        state=1;
    }
    e->movement->spriteBox->x = 128 * ((2 * e->movement->direction) + state);
    if(!isStarted_Timer(e->shootTimer))
    {
        e->movement->animationStep = (e->movement->animationStep + time) % 1000;
        step = abs((e->movement->animationStep / 250) - 2);
        e->movement->spriteBox->y = (Sint16) (224 * step);
    }
    else if(getTicksStart_Timer(e->shootTimer)<800)
    {
        e->movement->animationStep = (e->movement->animationStep + time) % 200;
        step = e->movement->animationStep/100;
        e->movement->spriteBox->y = (Sint16) (672 * step);
    }
    else
    {
        e->movement->animationStep-=time;
        e->movement->spriteBox->y = (Sint16) (672);
    }
}

extern void punch(Data* data, Entity* e, Coordinate* target, float maxhealth, Tiles** map) {
    int panick=1;
    if(e->health>maxhealth/2)
    {

        if (e->movement->animationStep < 0) {
            data->dungeonScene->sound->mobsAttack->arm = 1;
            e->movement->velocity->x = 0;
            e->movement->velocity->y = 0;
        }
    }
    else {
        panick=2;
        if (getTicksStart_Timer(e->shootTimer) > 3000 && e->movement->animationStep < 0) {
            data->dungeonScene->sound->mobsAttack->arm = 1;
            e->movement->velocity->x = 0;
            e->movement->velocity->y = 0;
        }
        else if(getTicksStart_Timer(e->shootTimer) < 3000)
        {
            char destType='X';
            int coordx=((int) e->movement->position->x+64)/64;
            int coordy=((int) e->movement->position->y+128)/64;
            Tiletype(map[coordy][coordx].type,&destType);
            if(destType=='W' || destType=='B')
            {
                data->dungeonScene->sound->mobsAttack->arm = 1;
                e->movement->velocity->x = 0;
                e->movement->velocity->y = 0;
            }
        }
    }

    if (!isStarted_Timer(e->shootTimer)) {
        start_Timer(e->shootTimer);
        e->movement->animationStep = 0;
    } else if (getTicksStart_Timer(e->shootTimer) > 800 && getTicksStart_Timer(e->shootTimer) < 3000 && !e->shootTimer->paused) {
        double Xdistance = target->x - e->movement->position->x - 32;
        double Ydistance = target->y - e->movement->position->y - 64;

        double angle;
        if (Xdistance != 0) {
            angle = atan(Ydistance / Xdistance);
        } else {
            angle = 1.57;
        }
        e->movement->velocity->x = (float) (fabs(cos(angle)) * sign(Xdistance))*panick;
        e->movement->velocity->y = (float) (fabs(sin(angle)) * sign(Ydistance))*panick;

        e->movement->animationStep = (int) (Ydistance / (e->movement->velocity->y*e->speed*0.06*panick));


        e->shootTimer->paused=true;
    } else if (getTicksStart_Timer(e->shootTimer) >= 3000 && e->shootTimer->paused)
    {
        double Xdistance = 431+(300*abs(e->movement->direction-1)) - e->movement->position->x;
        double Ydistance = 186 - e->movement->position->y;
        double angle;
        if (Xdistance != 0) {
            angle = atan(Ydistance / Xdistance);
        } else {
            angle = 1.57;
        }
        e->movement->velocity->x = (float) (fabs(cos(angle)) * sign(Xdistance));
        e->movement->velocity->y = (float) (fabs(sin(angle)) * sign(Ydistance));

        e->movement->animationStep = (int) (Ydistance / (e->movement->velocity->y*e->speed*0.06));


        e->shootTimer->paused=false;
    } else if(getTicksStart_Timer(e->shootTimer) >= 3010 && e->movement->animationStep < 0)
    {
        e->movement->velocity->x = 0;
        e->movement->velocity->y = 0;
        stop_Timer(e->shootTimer);
    }
}


