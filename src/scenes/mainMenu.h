#include <stdbool.h>

#include "../image.h"
#include "../data.h"

#ifndef FREE_PROJECT_MAINMENU_H
#define FREE_PROJECT_MAINMENU_H

extern void assets_Scene_mainMenu(ImageCollector* myImageCollector, bool loadOrUnload);
extern void eventProcess_Scene_mainMenu(SDL_Event event, Data* data);
extern void renderScene_Scene_mainMenu(SDL_Surface* window, ImageCollector* myImageCollector, Data* data);
extern void logicProcess_Scene_mainMenu(Data* data);

static SDL_Surface* getMainMenu(ImageCollector* myImageCollector);

static void moveMainMenuSelector(int direction);
static void enterMainMenu();
static int getCurrentMainMenuSelector();

#endif //FREE_PROJECT_MAINMENU_H
