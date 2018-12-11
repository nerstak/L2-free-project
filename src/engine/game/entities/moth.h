#ifndef FREE_PROJECT_ENGINE_GAME_ENTITIES_MOTH_H
#define FREE_PROJECT_ENGINE_GAME_ENTITIES_MOTH_H

#include "../../data.h"
#include "main.h"

typedef struct E_Moth {
} E_Moth;

extern E_Moth* init_EMoth();
extern void clean_EMoth(E_Moth** p);

extern void ai_EMoth(Entity* e, Data* data);
extern void animate_EMoth(Entity* e, double x, int time);

#endif //FREE_PROJECT_ENGINE_GAME_ENTITIES_MOTH_H
