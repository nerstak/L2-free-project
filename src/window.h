#include <SDL/SDL_video.h>

#ifndef FREE_PROJECT_WINDOW_H
#define FREE_PROJECT_WINDOW_H

extern void initWindow();
static void cleanWindow();

extern void renderScreen();

extern void loadSurface(SDL_Surface* src, SDL_Surface* dest, SDL_Rect offset);

#endif //FREE_PROJECT_WINDOW_H
