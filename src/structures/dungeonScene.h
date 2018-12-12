#ifndef FREE_PROJECT_STRUCTURES_DUNGEONSCENE_H
#define FREE_PROJECT_STRUCTURES_DUNGEONSCENE_H

#include "../engine/game/dungeon/dungeon.h"

typedef struct dungeonScene_t {
    Dungeon* dungeon;
    Room* currentRoom;
    char** layoutsPath;
    size_t layoutsLength;
    int moveTo;
    int askCombat;
    int actionProcess;
    int keyValue;

    SDL_Surface* pauseBg;
} dungeonScene_t;

#endif //FREE_PROJECT_STRUCTURES_DUNGEONSCENE_H
