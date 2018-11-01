#include "inventory.h"

#ifndef FREE_PROJECT_DATAS_H
#define FREE_PROJECT_DATAS_H

#include "player.h"

typedef struct mainMenu_t {
    int position;
} mainMenu_t;

typedef struct shop_t {
    int n_selected;
    slot_inventory * selected;
    int ask_action;
    slot_inventory * shop_inv;
    slot_inventory * player_inv;
} shop_t;

typedef struct Data {
    struct mainMenu_t* mainMenu;
    struct shop_t* shop;
    struct Player * Isaac;
} Data;



extern Data* init_Data();
extern void clean_Data(Data** myData);

#endif //FREE_PROJECT_DATAS_H
