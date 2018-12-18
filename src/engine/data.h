#ifndef FREE_PROJECT_ENGINE_DATA_H
#define FREE_PROJECT_ENGINE_DATA_H

#include "../structures/mainMenu.h"
#include "../structures/shop.h"
#include "../structures/lobby.h"
#include "../structures/dungeonScene.h"
#include "../structures/inventory.h"
#include "../structures/options.h"
#include "../structures/pauseMenu.h"
#include "game/player.h"
#include "game/inventory.h"
#include "game/plants.h"
#include "game/entities/main.h"

typedef struct Data {
    struct referenceTable* referenceItems;
    struct inventory_t* inventory;
    struct lobby_t* lobby;
    struct mainMenu_t* mainMenu;
    struct options_t* options;
    struct pauseMenu_t* pauseMenu;
    struct shop_t* shop;
    struct field_t* field;
    struct dungeonScene_t* dungeonScene;
    struct Player* Isaac;
    int stop;

    EntityList* entities; //TEMP because theres no monsters in the lobby but I still need to test this shit
    EntityList* dyingEntities;
} Data;

/**
 * Create a Data object
 * @return a Data object
 */
extern Data* init_Data();
/**
 * Clean a Data object
 * @param p a double pointer to a Data object
 */
extern void clean_Data(Data** myData);

#endif //FREE_PROJECT_ENGINE_DATA_H
