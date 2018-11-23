#ifndef FREE_PROJECT_STRUCTURES_LOBBY_H
#define FREE_PROJECT_STRUCTURES_LOBBY_H

#include "../layout.h"

typedef struct lobby_t{
    Layout* layout;
    int askAction;
    int askMove;
    int menuHouse;
    int counterPressKey;
    //TODO: Add everything we need
}lobby_t;

#endif //FREE_PROJECT_STRUCTURES_LOBBY_H
