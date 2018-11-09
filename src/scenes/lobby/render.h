#ifndef FREE_PROJECT_LOBBY_RENDER_H
#define FREE_PROJECT_LOBBY_RENDER_H

#include <SDL_video.h>
#include "../../image.h"
#include "../../ttf.h"
#include "../../data.h"

extern void renderScene_Scene_lobby(SDL_Surface* window, ImageCollector* myImageCollector, FontCollector* myFontCollector, Data* data);

#endif //FREE_PROJECT_LOBBY_RENDER_H
