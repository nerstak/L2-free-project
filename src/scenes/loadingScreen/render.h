#ifndef FREE_PROJECT_LOADINGSCREEN_RENDER_H
#define FREE_PROJECT_LOADINGSCREEN_RENDER_H

#include <SDL/SDL.h>

#include "../../engine/collectors/image.h"
#include "../../engine/collectors/ttf.h"
#include "../../data.h"
#include "../../engine/main.h"

extern void renderScene_Scene_loadingScreen(SDL_Surface* window, Engine* engine, Data* data);

#endif //FREE_PROJECT_LOADINGSCREEN_RENDER_H
