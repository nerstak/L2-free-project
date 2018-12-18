#include <stdlib.h>
#include <math.h>

#include "projectile.h"
#include "main.h"
#include "../../../utils/math.h"
#include "../movement.h"
#include "../combat.h"


extern void shoot_Projectile(Data * data, Coordinate * source, float v, float damage, int life_time,int type)
{
    EntityList * bullet= init_EntityNode(PROJECTILE, data->dungeonScene->difficulty);
    bullet->data->movement->position=source;

    double Xdistance= data->Isaac->movement->hitBox->x + 32 - source->x;
    double Ydistance= data->Isaac->movement->hitBox->y + 32 - source->y;

    double angle;
    if(Xdistance != 0) {
        angle = atan(Ydistance / Xdistance);
    } else {
        angle = 1.57;
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

    char destType='X';
    int coordx=((int) e->movement->position->x+8)/64;
    int coordy=((int) e->movement->position->y+8)/64;
    Tiletype(data->dungeonScene->currentRoom->layout->map[coordy][coordx].type,&destType);
    if(destType=='W' || destType=='B')
    {
        e->health=0;
    }

    damage_Entity(e,data,0,0);



    animate_EProjectile(e, timeChange);
}
extern void animate_EProjectile(Entity* e, int time)
{
    e->movement->animationStep= (e->movement->animationStep+time)%300;
    e->movement->spriteBox->x=(e->movement->animationStep / 100) *16;
}


