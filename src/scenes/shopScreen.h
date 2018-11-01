#include <stdbool.h>

#include "../image.h"
#include "../data.h"
#include "../ttf.h"

#ifndef FREE_PROJECT_SHOPSCREEN_H
#define FREE_PROJECT_SHOPSCREEN_H

extern void assets_Scene_shop(ImageCollector* myImageCollector, bool loadOrUnload);
extern void init_Scene_shop(Data* data, bool loadOrUnload);
extern void eventProcess_Scene_shop(SDL_Event event, Data* data);
extern void renderScene_Scene_shop(SDL_Surface* window, ImageCollector* myImageCollector, FontCollector* myFontCollector, Data* data);
extern void logicProcess_Scene_shop(Data* data);

#endif //FREE_PROJECT_SHOPSCREEN_H
