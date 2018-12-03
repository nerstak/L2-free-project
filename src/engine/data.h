#ifndef FREE_PROJECT_ENGINE_DATA_H
#define FREE_PROJECT_ENGINE_DATA_H

#include "../structures/mainMenu.h"
#include "../structures/shop.h"
#include "../structures/lobby.h"
#include "../structures/inventory.h"
#include "../structures/options.h"
#include "../structures/dungeonScene.h"
#include "game/player.h"
#include "game/inventory.h"
#include "game/plants.h"

typedef struct Data {
    struct referenceTable* referenceItems;
    struct inventory_t* inventory;
    struct lobby_t* lobby;
    struct mainMenu_t* mainMenu;
    struct options_t* options;
    struct shop_t* shop;
    struct field_t* field;
    struct dungeonScene_t* dungeonScene;
    struct Player* Isaac;
    int stop;
} Data;

extern Data* init_Data();
extern void clean_Data(Data** myData);

#endif //FREE_PROJECT_ENGINE_DATA_H
