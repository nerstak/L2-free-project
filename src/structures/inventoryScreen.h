#ifndef FREE_PROJECT_STRUCTURES_INVENTORYSCREEN_H
#define FREE_PROJECT_STRUCTURES_INVENTORYSCREEN_H
#include "../inventory.h"
#include "../timer.h"

typedef struct inventory_t {
    int askAction;
    int askDeletion;
    int nSelected;
    char messageUsed[100];
    SlotInventory * selected;
    Timer* timerMessage;
} inventory_t;

#endif //FREE_PROJECT_STRUCTURES_INVENTORYSCREEN_H
