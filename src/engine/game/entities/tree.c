#include <stdlib.h>
#include <math.h>

#include "tree.h"
#include "main.h"
#include "../../../utils/math.h"
#include "../movement.h"
#include "projectile.h"

extern void ai_ETree(Entity* e, Data* data) {
    // Timer to get the time since the last frame of movement
    int timeChange = lap_Timer(e->movement->timeSince);
    if(timeChange > 300 || timeChange<-300) {
        timeChange = 0;
    }

    double Xdistance= data->Isaac->movement->position->x - e->movement->position->x;
    double Ydistance= data->Isaac->movement->position->y - e->movement->position->y;

    double angle;
    if(Xdistance != 0) {
        angle = atan(Ydistance / Xdistance);
    } else {
        angle = 0;
    }

    double dist = fabs(Xdistance) / fabs(cos(angle));
    if(dist > 300 && !e->attackTimer->started) {
        if(!isPaused_Timer(e->shootTimer))
        {
            pause_Timer(e->shootTimer);
        }

        e->movement->velocity->x += fabs(cos(angle)) * sign(Xdistance) * timeChange * 0.03;
        e->movement->velocity->y += fabs(sin(angle)) * sign(Ydistance) * timeChange * 0.03;

        if (e->movement->velocity->x != 0) {
            angle = atanf(e->movement->velocity->y / e->movement->velocity->x);
        }

        processVelocity_Movement(&(e->movement->velocity->x), timeChange, (2 * fabs(cos(angle))), 0); //Dampens and caps velocity
        processVelocity_Movement(&(e->movement->velocity->y), timeChange, (2 * fabs(sin(angle))), 0);


    } else if(e->attackTimer->started) {
        if(!isPaused_Timer(e->shootTimer))
        {
            pause_Timer(e->shootTimer);
        }

        cap_Timer(e->attackTimer,500);

        if (e->movement->velocity->x != 0) {
            angle = atanf(e->movement->velocity->y / e->movement->velocity->x);
        }

        processVelocity_Movement(&(e->movement->velocity->x), timeChange, (2 * fabs(cos(angle))), 0.05); //Dampens and caps velocity
        processVelocity_Movement(&(e->movement->velocity->y), timeChange, (2 * fabs(sin(angle))), 0.05);

    }
    else if(e->shootTimer->started)
    {
        if(isPaused_Timer(e->shootTimer))
        {
            unpause_Timer(e->shootTimer);
        }

        cap_Timer(e->shootTimer,1000);


        if (e->movement->velocity->x != 0) {
            angle = atanf(e->movement->velocity->y / e->movement->velocity->x);
        }
        processVelocity_Movement(&(e->movement->velocity->x), timeChange,(2 * fabs(cos(angle))), 0.05); //Dampens and caps velocity
        processVelocity_Movement(&(e->movement->velocity->y), timeChange,(2 * fabs(sin(angle))), 0.05);

    }
    else {
        Coordinate* source=malloc(sizeof(Coordinate));
        source->x=e->movement->position->x+(64*abs(e->movement->direction-1));
        source->y=e->movement->position->y+52;

        shoot_Projectile(data,source,3,e->damage,1200,e->type);
        lap_Timer(e->shootTimer);

        if (e->movement->velocity->x != 0) {
            angle = atanf(e->movement->velocity->y / e->movement->velocity->x);
        }

        processVelocity_Movement(&(e->movement->velocity->x), timeChange, (2 * fabs(cos(angle))), 0.05); //Dampens and caps velocity
        processVelocity_Movement(&(e->movement->velocity->y), timeChange, (2 * fabs(sin(angle))), 0.05);


    }

    e->movement->position->x+=e->movement->velocity->x * timeChange * 0.06 * e->speed;
    e->movement->position->y+=e->movement->velocity->y * timeChange * 0.06 * e->speed;

    e->movement->hitBox->x = (Sint16) (e->movement->position->x);
    e->movement->hitBox->y = (Sint16) (e->movement->position->y+12);

    Xdistance= data->Isaac->movement->position->x - e->movement->position->x;
    Ydistance= data->Isaac->movement->position->y - e->movement->position->y;

    animate_ETree(e, Xdistance, timeChange);
    damage_Entity(e, data, Xdistance, Ydistance);
}

extern void animate_ETree(Entity* e, double x, int time) {
    if (x > 0) {
        e->movement->direction = 0;
    } else {
        e->movement->direction = 1;
    }

    int shooting=0;

    if(e->shootTimer->started && !e->shootTimer->paused)
    {
        shooting=2;
    }


    e->movement->spriteBox->y = (Sint16) ((e->movement->direction+ shooting )* 96);

    e->movement->animationStep = (e->movement->animationStep + time) % 800;
    e->movement->spriteBox->x = (Sint16) abs((((e->movement->animationStep / 200) - 2)) * 64);
}