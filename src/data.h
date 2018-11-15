#ifndef FREE_PROJECT_DATAS_H
#define FREE_PROJECT_DATAS_H

#include "structures/mainMenu.h"
#include "structures/shopScreen.h"
#include "structures/lobby.h"
#include "player.h"
#include "inventory.h"

typedef struct Data {
    struct SlotInventory* referenceItems;
    struct mainMenu_t* mainMenu;
    struct shop_t* shop;
    struct Player * Isaac;
} Data;

extern Data* init_Data();
extern void clean_Data(Data** myData);

#endif //FREE_PROJECT_DATAS_H
