#include <stdlib.h>

#include "worm.h"
#include "main.h"
#include "../../../utils/math.h"
#include "../movement.h"
#include "projectile.h"

extern E_Worm* init_EWorm() {
    E_Worm* result = NULL;
    result = malloc(1 * sizeof(E_Worm));

    if (result == NULL) {
        exit(EXIT_FAILURE);
    }

    // Default value



    return result;
}

extern void clean_EWorm(E_Worm** p) {
    if ((*p) != NULL) {
        free((*p));
        (*p) = NULL;
    }
}

extern void ai_EWorm(Entity* e, Data* data)
{
    int timeChange = lap_Timer(e->movement->timeSince);
    if(timeChange > 300 || timeChange<-300) {
        timeChange = 0;
    }

    e->movement->hitBox->x = (Sint16) (e->movement->position->x);
    e->movement->hitBox->y = (Sint16) (e->movement->position->y);

    if(e->attackTimer->started) {
        cap_Timer(e->attackTimer,500);
    }
    else if(e->shootTimer->started){
        cap_Timer(e->shootTimer,2000);
    }
    else
    {
        Coordinate* source=malloc(sizeof(Coordinate));
        source->x=e->movement->position->x+32;
        source->y=e->movement->position->y;

        shoot_Projectile(data,source,5,e->damage,1300,e->type);
        lap_Timer(e->shootTimer);
    }

    animate_EWorm(e,timeChange);
    damage_Entity(e, data, 0, 0);
}



extern void animate_EWorm(Entity* e, int time)
{

    e->movement->animationStep = (e->movement->animationStep + time) % 1100;
    int step=abs( (e->movement->animationStep / 100) - 5);
    e->movement->spriteBox->x= 96*step;
}