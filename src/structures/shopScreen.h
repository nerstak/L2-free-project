#ifndef FREE_PROJECT_STRUCTURES_SHOP_H
#define FREE_PROJECT_STRUCTURES_SHOP_H

#include "../inventory.h"

typedef struct shop_t {
    int n_selected;
    SlotInventory * selected;
    int ask_action;
    SlotInventory * shop_inv;
} shop_t;

#endif //FREE_PROJECT_STRUCTURES_SHOP_H
