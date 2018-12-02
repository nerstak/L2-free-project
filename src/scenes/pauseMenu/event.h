#ifndef FREE_PROJECT_PAUSEMENU_EVENT_H
#define FREE_PROJECT_PAUSEMENU_EVENT_H

#include <SDL/SDL.h>

#include "../../engine/data.h"
#include "../../engine/main.h"

extern void eventProcess_Scene_pauseMenu(SDL_Event event, Engine* engine, Data* data);

#endif