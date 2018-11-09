#ifndef FREE_PROJECT_LOADINGSCREEN_RENDER_H
#define FREE_PROJECT_LOADINGSCREEN_RENDER_H

#include <SDL/SDL.h>

#include "../../image.h"
#include "../../ttf.h"
#include "../../data.h"

extern void renderScene_Scene_loadingScreen(SDL_Surface* window, ImageCollector* myImageCollector, FontCollector* myFontCollector, Data* data);

#endif //FREE_PROJECT_LOADINGSCREEN_RENDER_H
