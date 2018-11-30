#ifndef FREE_PROJECT_WINDOW_H
#define FREE_PROJECT_WINDOW_H

#include <SDL/SDL.h>

extern void init_Window();

extern void renderScreen();

extern void applySurface_Window(SDL_Surface* src, SDL_Surface* dest, SDL_Rect offset);

#endif //FREE_PROJECT_WINDOW_H
