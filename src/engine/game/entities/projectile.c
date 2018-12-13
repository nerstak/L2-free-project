#include <stdlib.h>
#include <math.h>

#include "projectile.h"
#include "main.h"
#include "../../../utils/math.h"
#include "../movement.h"
#include "../combat.h"

extern E_Projectile* init_EProjectile()
{
    E_Projectile* result = NULL;
    result = malloc(1 * sizeof(E_Projectile));

    if (result == NULL) {
        exit(EXIT_FAILURE);
    }

    // Default value

    return result;
}

extern void clean_EProjectile(E_Projectile** p)
{
    if ((*p) != NULL) {
        free((*p));
        (*p) = NULL;
    }
}

extern void shoot_Projectile(Data * data, Coordinate * source, float v, float damage, int life_time,int type)
{
    EntityList * bullet=init_EntityNode(PROJECTILE);
    bullet->data->movement->position=source;

    double Xdistance= data->Isaac->movement->position->x + 16 - source->x;
    double Ydistance= data->Isaac->movement->position->y + 48 - source->y;

    double angle;
    if(Xdistance != 0) {
        angle = atan(Ydistance / Xdistance);
    } else {
        angle = 0;
    }

    bullet->data->movement->velocity->x= fabs(cos(angle)) * sign(Xdistance);
    bullet->data->movement->velocity->y= fabs(sin(angle)) * sign(Ydistance);


    bullet->data->damage=damage;
    bullet->data->speed=v;
    bullet->data->health=life_time;

    bullet->data->movement->direction=type;

    append_EntityNode(bullet,&(data->entities));
}


extern void ai_EProjectile(Entity* e, Data* data)
{

    int timeChange = lap_Timer(e->movement->timeSince);
    if(timeChange > 300 || timeChange<-300) {
        timeChange = 0;
    }
    e->health-=timeChange;


    e->movement->position->x+=e->movement->velocity->x * timeChange * 0.06 * e->speed;
    e->movement->position->y+=e->movement->velocity->y * timeChange * 0.06 * e->speed;

    e->movement->hitBox->x = (Sint16) e->movement->position->x;
    e->movement->hitBox->y = (Sint16) e->movement->position->y;

    if(BoxCollision(e->movement->hitBox,data->Isaac->movement->hitBox))
    {
        start_Timer(data->Isaac->invulnerabilityTimer);
        alterHealth_Player(data->Isaac, - e->damage, 'c');
        e->health=0;
    }

    animate_EProjectile(e, timeChange);
}
extern void animate_EProjectile(Entity* e, int time)
{
    e->movement->animationStep= (e->movement->animationStep+time)%300;
    e->movement->spriteBox->x=(e->movement->animationStep / 100) *16;
}


