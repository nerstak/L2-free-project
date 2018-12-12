#include <stdlib.h>
#include <math.h>

#include "projectile.h"
#include "main.h"
#include "../../../utils/math.h"
#include "../movement.h"

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

extern void shoot_Projectile(Data * data, Coordinate * source, float v, float damage, int life_time)
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
    bullet->data->movement->velocity->y= fabs(sin(angle)) * sign(Xdistance);

    bullet->data->damage=damage;
    bullet->data->speed=v;
    bullet->data->health=life_time;

    append_EntityNode(bullet,&(data->entities));
}


extern void ai_EProjectile(Entity* e, Data* data);
extern void animate_EProjectile(Entity* e, int time);


