#ifndef FREE_PROJECT_ENGINE_GAME_PLAYER_H
#define FREE_PROJECT_ENGINE_GAME_PLAYER_H

#include "inventory.h"
#include <SDL/SDL.h>

typedef struct coordinates_entity {
    float x;
    float y;
} coordinates_entity;

typedef struct GameStats {
    int death;
    int dungeons;
    int kills;
}GameStats;


typedef struct Weapon {
    char name[20];
    char description[100];
    float damage;
    float agility;
}Weapon;

typedef struct MovementValues {
    coordinates_entity * pos;
    coordinates_entity * velocity;
    int step; //animation step
    int direction;
    SDL_Rect * SpriteBox;
    SDL_Rect * Hitbox;
    int timesince;
}MovementValues;

typedef struct CombatValues {
    int step; //animation step
    int direction;
    SDL_Rect * SpriteBox;
    SDL_Rect * WeaponHitbox;
    int timesince;
}CombatValues;


typedef struct Player {
    int money;
    MovementValues * movement;
    CombatValues * combat;
    SlotInventory * inventory;
    int size_inventory;
    Weapon * weapons;
    struct GameStats* gameStats;
    generalStats* stats;
    char save_name[20];
    int day;
} Player;

/**
 * Initialise the Object Player
 * @return Pointer to Player Object
 */
extern Player* initPlayer();

/**
 * Cleaning and free a Player Object
 */
extern void freePlayer(Player** Isaac);

/**
 * Alter the money of the Player, respecting boundaries
 * @param Isaac pointer to the Player Object
 * @param alterMoney Integer of the modification of money to do
 * @return Integer of the proceeding of the operation (0: Not Done; 1: Done)
 */
extern int alterMoney(Player* Isaac, int alterMoney);

/**
 * Alter the health of the Player, respecting boundaries
 * @param Isaac pointer to the Player Object
 * @param alterHealth Integer of the modification of health to do
 * @param type char. 'b' to modify basic stats (def), 'c' for current stats (temp)
 */
extern void alterHealth(Player* Isaac, float alterHealth, char type);

/**
 * Alter the speed of the Player, respecting boundaries
 * @param Isaac pointer to the Player Object
 * @param alterSpeed Integer of the modification of speed to do
 * @param type char. 'b' to modify basic stats (def), 'c' for current stats (temp)
 */
extern void alterSpeed(Player* Isaac, float alterSpeed, char type);

/**
 * Alter the agility of the Player, respecting boundaries
 * @param Isaac pointer to the Player Object
 * @param alterAgility Integer of the modification of agility to do
 * @param type char. 'b' to modify basic stats (def), 'c' for current stats (temp)
 */
extern void alterAgility(Player* Isaac, float alterAgility, char type);

/**
 * Alter the damage of the Player, respecting boundaries
 * @param Isaac pointer to the Player Object
 * @param alterDamage Integer of the modification of damage to do
 * @param type char. 'b' to modify basic stats (def), 'c' for current stats (temp)
 */
extern void alterDamage(Player* Isaac, float alterDamage, char type);

#endif // FREE_PROJECT_ENGINE_GAME_PLAYER_H
