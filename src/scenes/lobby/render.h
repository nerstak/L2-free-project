#ifndef FREE_PROJECT_LOBBY_RENDER_H
#define FREE_PROJECT_LOBBY_RENDER_H

#include <SDL_video.h>
#include "../../engine/collectors/image.h"
#include "../../engine/collectors/ttf.h"
#include "../../data.h"
#include "../../engine/main.h"

extern void renderScene_Scene_lobby(SDL_Surface* window, Engine* engine, Data* data);

#endif //FREE_PROJECT_LOBBY_RENDER_H
