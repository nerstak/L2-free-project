#include "image.h"

#include <SDL/SDL_video.h>

#ifndef FREE_PROJECT_MENU_H
#define FREE_PROJECT_MENU_H

extern void displayMainMenu(SDL_Surface* window, ImageCollector* myImageCollector);

extern void moveMainMenuSelector(int direction);
extern void enterMainMenu();
extern int getCurrentMainMenuSelector();

static SDL_Surface* getMainMenu(ImageCollector* myImageCollector);

#endif //FREE_PROJECT_MENU_H
