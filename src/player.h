#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "inventory.h"
#include <SDL/SDL.h>

typedef struct coordinates_entity {
    float x;
    float y;
} coordinates_entity;


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
    int timesince;
}MovementValues;


typedef struct Player {
    int money;
    MovementValues * movement;
    SlotInventory * inventory;
    int size_inventory;
    Weapon * weapons;
    struct stats_entity* current_stats;
    struct stats_entity* basic_stats;
    struct stats_entity* maxStats;
    char save_name[20];
    int day;
} Player;

extern Player* initPlayer();
int alterMoney(Player* Isaac, int money_change);
void alterHealth(Player* Isaac, float alterHealth, char type);
void alterSpeed(Player* Isaac, float alterSpeed, char type);
void alterAgility(Player* Isaac, float alterAgility, char type);
void alterDamage(Player* Isaac, float alterDamage, char type);

#endif // PLAYER_H_INCLUDED
