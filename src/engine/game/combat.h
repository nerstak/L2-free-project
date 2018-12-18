#ifndef FREE_PROJECT_ENGINE_GAME_COMBAT_H
#define FREE_PROJECT_ENGINE_GAME_COMBAT_H

#include <stdbool.h>
#include "../data.h"
#include "../main.h"

/**
 * Process the combat for the Player
 * @param data a pointer to a Data Object
 * @param direction a pointer to an int of the direction where the player is looking
 */
extern void ProcessCombat(Engine* engine, Data * data, int * direction);
/**
 * Process the animation of fight for the Player
 * @param combat a pointer to a CombatValues Object
 * @param time int of the time spent
 * @param agility int of the Agility Stat of the Player
 */
extern void CombatAnimation(CombatValues * combat,int time,float agility,float agilitywep);
/**
 * Select the correct sprite for the player in fight
 * @param combat a pointer to a CombatValues Object
 * @param type a char of the type of the cell
 * @param engine a pointer an Engine Object
 */
extern void CombatSprite(CombatValues * combat,char type, Engine* engine);
/**
 * Set the hitbox of the Weapon
 * @param Isaac a pointer to a Player Object
 */
extern void SetCombatHitbox(Player * Isaac,char type);
/**
 * Check if any collision append
 * @param box1 a pointer to a SDL_Rect Object of the first hitbox
 * @param box2 a pointer to a SDL_Rect Object of the second hitbox
 * @return a bool attesting the collision
 */
extern bool BoxCollision(SDL_Rect * box1, SDL_Rect * box2);
/**
 * Check if a point is within an hitbox
 * @param xPoint int of the X-Coordinate of the point
 * @param yPoint int of the Y-Coordinate of the point
 * @param boxtarget a pointer to a SDL_Rect of the hitbox
 * @return a bool attesting the presence or not of the point inside the hitbox
 */
extern bool CheckBox(int xPoint, int yPoint, SDL_Rect * boxtarget);
#endif // FREE_PROJECT_ENGINE_GAME_COMBAT_H
