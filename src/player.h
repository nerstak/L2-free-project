#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include "data.h"


typedef struct coordinates_entity {
    int x;
    int y;
} coordinates_entity;

typedef struct slot_inventory {
    char * name_item;
    int quantity;
    struct slot_inventory * next;
} slot_inventory;

typedef struct stats_entity {
    int health;
    int damage;
    int speed;
    int ability;
} stats_entity;

typedef struct Player {
    coordinates_entity * pos;
    int money;
    slot_inventory * inventory;
    slot_inventory * equipment;
    stats_entity * current_stats;
    stats_entity * basic_stats;
} Player;

int alter_money(Player *Isaac, int money_change);
void alter_health(Player *Isaac, int alter_health);

void player_logic_lobby(Data* data);

#endif // PLAYER_H_INCLUDED
