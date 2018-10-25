#include "window.h"

#include "game.h"

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

SDL_Surface* window = NULL;

extern void initWindow() {
    SDL_Init(SDL_INIT_VIDEO); // We only init VIDEO_mod for now
    TTF_Init();

    window = SDL_SetVideoMode(1280, 720, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    if (window == NULL) {
        fprintf(stderr, "Failed to load graphical view: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_WM_SetCaption("free_project v0.0.1 Alpha", NULL);

    gameLoop(window);

    cleanWindow();

    SDL_Quit();
    TTF_Quit();
}

static void cleanWindow() {
    SDL_FreeSurface(window);
}

extern void renderScreen() {
    SDL_Flip(window);
    SDL_FillRect(window, &window->clip_rect, SDL_MapRGB(window->format, 0, 0, 0)); // Erase the screen please
}

extern void loadSurface(SDL_Surface* src, SDL_Surface* dest, SDL_Rect offset) {
    SDL_BlitSurface(src, NULL, dest, &offset);
}
