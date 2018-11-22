#ifndef FREE_PROJECT_STRUCTURES_INVENTORYSCREEN_H
#define FREE_PROJECT_STRUCTURES_INVENTORYSCREEN_H
#include "../inventory.h"

typedef struct inventory_t {
    int askAction;
    int askDeletion;
    int nSelected;
    SlotInventory * selected;
} inventory_t;

#endif //FREE_PROJECT_STRUCTURES_INVENTORYSCREEN_H
