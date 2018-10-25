#include "../image.h"
#include "../asset.h"
#include "../data.h"

#ifndef LOBBY_H
#define LOBBY_H

extern void assets_Scene_lobby(ImageCollector* myImageCollector, bool loadOrUnload);
extern void init_Scene_lobby(Data* data, bool loadOrUnload);
extern void eventProcess_Scene_lobby(SDL_Event event, Data* data);
extern void renderScene_Scene_lobby(SDL_Surface* window, ImageCollector* myImageCollector, Data* data);
extern void logicProcess_Scene_lobby(Data* data);

#endif //LOBBY_H
