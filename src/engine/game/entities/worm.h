#ifndef FREE_PROJECT_ENGINE_GAME_ENTITIES_WORM_H
#define FREE_PROJECT_ENGINE_GAME_ENTITIES_WORM_H

#include "../../data.h"
#include "main.h"
typedef struct E_Worm {
} E_Worm;

extern E_Worm* init_EWorm();

extern void clean_EWorm(E_Worm** p);

extern void ai_EWorm(Entity* e, Data* data);
extern void animate_EWorm(Entity* e, int time);
#endif //FREE_PROJECT_ENGINE_GAME_ENTITIES_WORM_H
