#ifndef FREE_PROJECT_ENGINE_GAME_ENTITIES_ARM_H
#define FREE_PROJECT_ENGINE_GAME_ENTITIES_ARM_H

#include "../../data.h"
#include "main.h"


extern void ai_EArm(Entity* e, Data* data,float maxhealth);
extern void animate_EArm(Entity* e, int time,float maxhealth);
extern void punch(Entity* e,Coordinate * target,float maxhealth,Tiles ** map);






#endif //FREE_PROJECT_ENGINE_GAME_ENTITIES_ARM_H