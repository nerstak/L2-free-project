#ifndef FREE_PROJECT_STRUCTURES_SHOP_H
#define FREE_PROJECT_STRUCTURES_SHOP_H

#include "../inventory.h"

typedef struct shop_t {
    int askAction;
    int askTransaction;
    int nSelected;
    int itemsInTransaction;
    int size_shop;
    SlotInventory * selected;
    SlotInventory * shop_inv;
} shop_t;

#endif //FREE_PROJECT_STRUCTURES_SHOP_H
