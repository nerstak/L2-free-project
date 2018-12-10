#ifndef FREE_PROJECT_ENGINE_GAME_COMBAT_H
#define FREE_PROJECT_ENGINE_GAME_COMBAT_H

#include <stdbool.h>
#include "../data.h"

extern void ProcessCombat(Data * data, int * direction);

extern void CombatAnimation(CombatValues * combat,int time,int agility);

extern void CombatSprite(CombatValues * combat);

extern void SetCombatHitbox(Player * Isaac);

extern bool BoxCollision(SDL_Rect * box1, SDL_Rect * box2);

extern bool CheckBox(int xPoint, int yPoint, SDL_Rect * boxtarget);
#endif // FREE_PROJECT_ENGINE_GAME_COMBAT_H
