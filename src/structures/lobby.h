#ifndef FREE_PROJECT_STRUCTURES_LOBBY_H
#define FREE_PROJECT_STRUCTURES_LOBBY_H

#include "../engine/game/layout.h"

enum actionLobby {NONE = 0, INVENTORY = 100, SLEEP = 1, GARDEN = 2, PLANT = 21, GOTO_DUNGEON = 22, WAIT = 23, SHOP = 3, PAUSE = 9};

typedef struct lobby_t{
    Layout* layout;
    int askAction;
    int askMove;
    int actionProcess;
    int counterPressKey;
    int counterPressKeyMove;
    struct Plant* actualPlant;
}lobby_t;

#endif //FREE_PROJECT_STRUCTURES_LOBBY_H
