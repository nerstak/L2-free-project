#include "../image.h"
#include "../asset.h"

#ifndef FREE_PROJECT_LOADINGSCREEN_H
#define FREE_PROJECT_LOADINGSCREEN_H

extern void assets_Scene_loadingScreen(ImageCollector* myImageCollector, bool loadOrUnload);
extern void eventProcess_Scene_loadingScreen();
extern void renderScene_Scene_loadingScreen(SDL_Surface* window, ImageCollector* myImageCollector);
extern void logicProcess_Scene_loadingScreen();

static SDL_Surface* getLoadingScreen(ImageCollector* myImageCollector);

#endif //FREE_PROJECT_LOADINGSCREEN_H
