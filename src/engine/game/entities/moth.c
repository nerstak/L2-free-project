#include <stdlib.h>
#include <math.h>

#include "moth.h"
#include "main.h"
#include "../../../utils/math.h"
#include "../movement.h"


extern void ai_EMoth(Entity* e, Data* data) {
    // Timer to get the time since the last frame of movement
    int timeChange = lap_Timer(e->movement->timeSince);
    if(timeChange > 300 || timeChange<-300) {
        timeChange = 0;
    }

    double Xdistance= data->Isaac->movement->position->x - 32 - e->movement->position->x;
    double Ydistance= data->Isaac->movement->position->y - e->movement->position->y;

    double angle;
    if(Xdistance != 0) {
        angle = atan(Ydistance / Xdistance);
    } else {
        angle = 0;
    }

    double dist = fabs(Xdistance) / fabs(cos(angle));
    if(dist < 400 && !e->attackTimer->started) {
        e->movement->velocity->x += fabs(cos(angle)) * sign(Xdistance) * timeChange * 0.06;
        e->movement->velocity->y += fabs(sin(angle)) * sign(Ydistance) * timeChange * 0.06;

        if (e->movement->velocity->x != 0) {
            angle = atanf(e->movement->velocity->y / e->movement->velocity->x);
        }

        processVelocity_Movement(&(e->movement->velocity->x), timeChange, (4 * fabs(cos(angle))), 0); //Dampens and caps velocity
        processVelocity_Movement(&(e->movement->velocity->y), timeChange, (4 * fabs(sin(angle))), 0);

        e->movement->position->x += ((rand()%3) - 1) * (timeChange*0.12);
        e->movement->position->y += ((rand()%3) - 1) * (timeChange*0.12);

    } else if(e->attackTimer->started) {
        cap_Timer(e->attackTimer,500);

        if (e->movement->velocity->x != 0) {
            angle = atanf(e->movement->velocity->y / e->movement->velocity->x);
        }

        processVelocity_Movement(&(e->movement->velocity->x), timeChange, (4 * fabs(cos(angle))), 0.05); //Dampens and caps velocity
        processVelocity_Movement(&(e->movement->velocity->y), timeChange, (4 * fabs(sin(angle))), 0.05);

    } else {
        processVelocity_Movement(&(e->movement->velocity->x), timeChange, (4 * fabs(cos(angle))), 1); //Dampens and caps velocity
        processVelocity_Movement(&(e->movement->velocity->y), timeChange, (4 * fabs(sin(angle))), 1);
    }

    //TODO: make a PosChange function
    e->movement->position->x+=e->movement->velocity->x * timeChange * 0.06 * e->speed;
    e->movement->position->y+=e->movement->velocity->y * timeChange * 0.06 * e->speed;

    e->movement->hitBox->x = (Sint16) (e->movement->position->x + 48);
    e->movement->hitBox->y = (Sint16) e->movement->position->y;

    animate_EMoth(e, Xdistance, timeChange);
    damage_Entity(e, data, Xdistance, Ydistance);
}

extern void animate_EMoth(Entity* e, double x, int time) {
    if (x > 0) {
        e->movement->direction = 1;
    } else {
        e->movement->direction = 0;
    }

    e->movement->spriteBox->y = (Sint16) (e->movement->direction * 96);

    if (!e->movement->velocity->x && !e->movement->velocity->y) {
        e->movement->spriteBox->x = 0;
    } else {
        e->movement->animationStep = (e->movement->animationStep + time) % 200;
        e->movement->spriteBox->x = (Sint16) (((e->movement->animationStep / 100) + 1) * 128);
    }
}