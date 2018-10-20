#include <stdbool.h>

#include "../image.h"

#ifndef FREE_PROJECT_MAINMENU_H
#define FREE_PROJECT_MAINMENU_H

extern void assets_Scene_mainMenu(ImageCollector* myImageCollector, bool loadOrUnload);
extern void eventProcess_Scene_mainMenu();
extern void renderScene_Scene_mainMenu(SDL_Surface* window, ImageCollector* myImageCollector);
extern void logicProcess_Scene_mainMenu();

static SDL_Surface* getMainMenu(ImageCollector* myImageCollector);

static void moveMainMenuSelector(int direction);
static void enterMainMenu();
static int getCurrentMainMenuSelector();

#endif //FREE_PROJECT_MAINMENU_H
