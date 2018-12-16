#ifndef FREE_PROJECT_ENGINE_GAME_ENTITIES_BOSS_H
#define FREE_PROJECT_ENGINE_GAME_ENTITIES_BOSS_H

#include "../../data.h"
#include "main.h"
typedef struct E_Boss {
    Entity * leftarm;
    Entity * rightarm;
    SDL_Rect * leftsprite;
    SDL_Rect * rightsprite;
} E_Boss;

extern E_Boss* init_EBoss(float maxhealth);
extern void clean_EBoss(E_Boss** p);

extern void ai_EBoss(Entity* e, Data* data);
extern void animate_EBoss(Entity* e, int time,E_Boss * arms);






#endif //FREE_PROJECT_ENGINE_GAME_ENTITIES_BOSS_H
