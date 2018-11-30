#ifndef COMBAT_H_INCLUDED
#define COMBAT_H_INCLUDED

extern void ProcessCombat(Data * data, int direction);

extern void CombatAnimation(CombatValues * combat,int time);

extern void CombatSprite(CombatValues * combat);

extern void SetCombatHitbox(Player * Isaac);

extern bool BoxCollision(SDL_Rect * box1, SDL_Rect * box2);

extern bool CheckBox(int xPoint, int yPoint, SDL_Rect * boxtarget);
#endif // COMBAT_H_INCLUDED
