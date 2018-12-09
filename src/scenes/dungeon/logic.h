#ifndef FREE_PROJECT_DUNGEON_LOGIC_H
#define FREE_PROJECT_DUNGEON_LOGIC_H

#include "../../engine/data.h"
#include "../../engine/main.h"

extern void logicProcess_Scene_dungeon(Engine* engine, Data* data);
extern void enterdoor(SDL_Rect * door, SDL_Rect * player,dungeonScene_t * room,int direction);

#endif //FREE_PROJECT_DUNGEON_LOGIC_H
