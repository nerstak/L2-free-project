#ifndef FREE_PROJECT_STRUCTURES_SHOP_H
#define FREE_PROJECT_STRUCTURES_SHOP_H

#include "../engine/game/inventory.h"
#include "../engine/timer.h"

typedef struct shop_t {
    int askAction;
    int askTransaction;
    int nSelected;
    int itemsInTransaction;
    int size_shop;
    char messageAction[100];
    SlotInventory * selected;
    SlotInventory * shop_inv;
    Timer* timerMessage;
} shop_t;

#endif //FREE_PROJECT_STRUCTURES_SHOP_H
