#ifndef FREE_PROJECT_ENGINE_GAME_PLAYER_H
#define FREE_PROJECT_ENGINE_GAME_PLAYER_H

#include <SDL/SDL.h>
#include "../timer.h"
#include "movement.h"
#include "inventory.h"

typedef struct GameStats {
    int death;
    int dungeons;
    int kills;
    int dungeonDay;
} GameStats;

typedef struct Weapon {
    char name[20];
    char description[100];
    float damage;
    float agility;
} Weapon;

/**
 * Initialise a Weapon Object
 * @return a pointer to a Weapon Object
 */
extern Weapon* init_Weapon();
/**
 * Free a Weapon Object
 * @param p a double pointer to a Weapon Object
 */
extern void clean_Weapon(Weapon** p);

typedef struct CombatValues {
    int animationStep;
    int direction;
    SDL_Rect* spriteBox;
    SDL_Rect* weaponHitBox;
    Timer* timeSince;
} CombatValues;

/**
 * Init a CombatValues Object
 * @return a pointer to a CombatValues Object
 */
extern CombatValues* init_Combat();
/**
 * Free a CombatValues Object
 * @param p a double pointer to a CombatValues Object
 */
extern void clean_Combat(CombatValues** p);

typedef struct Player {
    int money;
    MovementValues* movement;
    CombatValues* combat;
    SlotInventory* inventory;
    int sizeInventory;
    Weapon* weapons;
    struct GameStats* gameStats;
    Timer* invulnerabilityTimer;
    generalStats* stats;
    char saveName[20];
    int day;
} Player;

/**
 * Initialise the Object Player
 * @return Pointer to Player Object
 */
extern Player* init_Player();

/**
 * Cleaning and free a Player Object
 */
extern void free_Player(Player** Isaac);

/**
 * Alter the money of the Player, respecting boundaries
 * @param Isaac pointer to the Player Object
 * @param alterMoney Integer of the modification of money to do
 * @return Integer of the proceeding of the operation (0: Not Done; 1: Done)
 */
extern int alterMoney_Player(Player* Isaac, int alterMoney);

/**
 * Alter the health of the Player, respecting boundaries
 * @param Isaac pointer to the Player Object
 * @param alterHealth Integer of the modification of health to do
 * @param type char. 'b' to modify basic stats (def), 'c' for current stats (temp)
 */
extern void alterHealth_Player(Player* Isaac, float alterHealth, char type);

/**
 * Alter the speed of the Player, respecting boundaries
 * @param Isaac pointer to the Player Object
 * @param alterSpeed Integer of the modification of speed to do
 * @param type char. 'b' to modify basic stats (def), 'c' for current stats (temp)
 */
extern void alterSpeed_Player(Player* Isaac, float alterSpeed, char type);

/**
 * Alter the agility of the Player, respecting boundaries
 * @param Isaac pointer to the Player Object
 * @param alterAgility Integer of the modification of agility to do
 * @param type char. 'b' to modify basic stats (def), 'c' for current stats (temp)
 */
extern void alterAgility_Player(Player* Isaac, float alterAgility, char type);

/**
 * Alter the damage of the Player, respecting boundaries
 * @param Isaac pointer to the Player Object
 * @param alterDamage Integer of the modification of damage to do
 * @param type char. 'b' to modify basic stats (def), 'c' for current stats (temp)
 */
extern void alterDamage_Player(Player* Isaac, float alterDamage, char type);

/**
 * Check if the player has more than 0 Health Point
 * @param Isaac a pointer to a Player Object
 * @return an int (0: dead; 1: alive)
 */
extern int isPlayerAlive(Player* Isaac);

/**
 * Set the current stats to the basic stats
 * @param Isaac a pointer to a Player Object
 */
extern void resetStats(Player* Isaac);
#endif // FREE_PROJECT_ENGINE_GAME_PLAYER_H
