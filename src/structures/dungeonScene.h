#ifndef FREE_PROJECT_STRUCTURES_DUNGEONSCENE_H
#define FREE_PROJECT_STRUCTURES_DUNGEONSCENE_H

#include "../engine/game/dungeon/dungeon.h"

typedef struct entities_bool {
    int moth;
    int worm;
    int boss;
} entities_bool;

typedef struct soundDungeon_t {
    int deathMob;
    int bossJustDefeated;
    entities_bool* mobsDamaged;
    entities_bool* mobsDisplacement;
    entities_bool* mobsAttack;
} soundDungeon_t;

typedef struct dungeonScene_t {
    Dungeon* dungeon;
    Room* currentRoom;
    char** layoutsPath;
    size_t layoutsLength;
    int moveTo;
    int askCombat;
    int actionProcess;
    int keyValue;

    soundDungeon_t* sound;

    SDL_Surface* pauseBg;
} dungeonScene_t;

#endif //FREE_PROJECT_STRUCTURES_DUNGEONSCENE_H
