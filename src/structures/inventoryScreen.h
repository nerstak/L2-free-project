#ifndef FREE_PROJECT_STRUCTURES_INVENTORYSCREEN_H
#define FREE_PROJECT_STRUCTURES_INVENTORYSCREEN_H
#include "../inventory.h"
#include "../timer.h"

enum actionInventory {I_NONE = 0, I_UP = -10, I_DOWN = 10, I_LEFT = -1, I_RIGHT = 1, I_ENTER = 5, I_DELETE = 8, I_LEAVE = 15};


typedef struct inventory_t {
    int askAction;
    int askDeletion;
    int nSelected;
    char messageUsed[100];
    SlotInventory * selected;
    Timer* timerMessage;
} inventory_t;

#endif //FREE_PROJECT_STRUCTURES_INVENTORYSCREEN_H
