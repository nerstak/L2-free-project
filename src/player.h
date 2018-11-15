#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "inventory.h"

/*
typedef struct coordinates_entity {
    int x;
    int y;
} coordinates_entity;
*/


typedef struct stats_entity {
    int health;
    int damage;
    int speed;
    int ability;
} stats_entity;

typedef struct Weapon {
    char name[20];
    char description[100];
    int damage;
    int swing_speed;
}Weapon;

typedef struct MovementValues {
    SDL_Rect * pos;
    SDL_Rect * velocity;
    int AnimationStep;
}MovementValues;


typedef struct Player {
    int money;
    MovementValues * movement;
    SlotInventory * inventory;
    int size_inventory;
    Weapon * weapons;
    stats_entity * current_stats;
    stats_entity * basic_stats;
    char save_name[20];
} Player;


int alter_money(Player *Isaac, int money_change);
void alter_health(Player *Isaac, int alter_health);

#endif // PLAYER_H_INCLUDED
