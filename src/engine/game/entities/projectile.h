#ifndef FREE_PROJECT_ENGINE_GAME_ENTITIES_PROJECTILE_H
#define FREE_PROJECT_ENGINE_GAME_ENTITIES_PROJECTILE_H

#include "../../data.h"
#include "main.h"


extern void shoot_Projectile(Data * data, Coordinate * source, float v, float damage, int life_time,int type);

extern void ai_EProjectile(Entity* e, Data* data);
extern void animate_EProjectile(Entity* e, int time);

#endif //FREE_PROJECT_ENGINE_GAME_ENTITIES_MOTH_H
