#ifndef FREE_PROJECT_STRUCTURES_DUNGEONSCENE_H
#define FREE_PROJECT_STRUCTURES_DUNGEONSCENE_H

#include "../engine/game/dungeon/dungeon.h"
#include "../engine/game/notification.h"

struct dungeonAssets_t {
    SDL_Surface* bg;
    SDL_Surface* obstacle;
    SDL_Surface* slow;
    SDL_Surface* hole;
};

typedef struct dungeonScene_t {
    Dungeon* dungeon;
    Room* currentRoom;
    char** layoutsPath;
    size_t layoutsLength;
    float difficulty;
    struct dungeonAssets_t dungeonAssets;

    int moveTo;
    int askCombat;
    int actionProcess;
    int keyValue;

    NotificationQueue* notificationQueue;

    SDL_Surface* pauseBg;
} dungeonScene_t;

#endif //FREE_PROJECT_STRUCTURES_DUNGEONSCENE_H
