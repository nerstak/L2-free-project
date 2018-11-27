#ifndef FREE_PROJECT_DATA_H
#define FREE_PROJECT_DATA_H

#include "structures/mainMenu.h"
#include "structures/shopScreen.h"
#include "structures/lobby.h"
#include "structures/inventoryScreen.h"
#include "player.h"
#include "inventory.h"
#include "plants.h"

typedef struct Data {
    struct referenceTable* referenceItems;
    struct inventory_t* inventory;
    struct lobby_t* lobby;
    struct mainMenu_t* mainMenu;
    struct shop_t* shop;
    struct field_t* field;
    struct Player* Isaac;
    int stop;
} Data;

extern Data* init_Data();
extern void clean_Data(Data** myData);

#endif //FREE_PROJECT_DATA_H
