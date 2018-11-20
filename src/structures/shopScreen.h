#ifndef FREE_PROJECT_STRUCTURES_SHOP_H
#define FREE_PROJECT_STRUCTURES_SHOP_H

#include "../inventory.h"

typedef struct shop_t {
    int nSelected;
    SlotInventory * selected;
    int askAction;
    SlotInventory * shop_inv;
    int size_shop;
} shop_t;

#endif //FREE_PROJECT_STRUCTURES_SHOP_H
