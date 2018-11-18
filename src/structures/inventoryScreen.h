#ifndef FREE_PROJECT_STRUCTURES_INVENTORYSCREEN_H
#define FREE_PROJECT_STRUCTURES_INVENTORYSCREEN_H
#include "../inventory.h"

typedef struct inventory_t {
    int nSelected;
    SlotInventory * selected;
    int askAction;
} inventory_t;

#endif //FREE_PROJECT_STRUCTURES_INVENTORYSCREEN_H
