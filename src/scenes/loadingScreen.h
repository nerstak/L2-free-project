#include "../image.h"
#include "../asset.h"
#include "../data.h"

#ifndef FREE_PROJECT_LOADINGSCREEN_H
#define FREE_PROJECT_LOADINGSCREEN_H

extern void assets_Scene_loadingScreen(ImageCollector* myImageCollector, bool loadOrUnload);
extern void init_Scene_loadingScreen(Data* data, bool loadOrUnload);
extern void eventProcess_Scene_loadingScreen(SDL_Event event, Data* data);
extern void renderScene_Scene_loadingScreen(SDL_Surface* window, ImageCollector* myImageCollector, Data* data);
extern void logicProcess_Scene_loadingScreen(Data* data);

static SDL_Surface* getLoadingScreen(ImageCollector* myImageCollector);

#endif //FREE_PROJECT_LOADINGSCREEN_H
