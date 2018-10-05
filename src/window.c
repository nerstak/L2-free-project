#include "window.h"

#include <SDL/SDL.h>

void initWindow() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Surface* window = NULL;
    window = SDL_SetVideoMode(1280, 720, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    if (window == NULL) {
        fprintf(stderr, "Failed to load graphical view: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_WM_SetCaption("free_project v0.0.1 Alpha", NULL);

    handleWindowExit();

    SDL_Quit();
}

void handleWindowExit() {
    int stop = 1;
    SDL_Event event;

    while (stop) {
        SDL_WaitEvent(&event);

        switch (event.type) {
            case SDL_QUIT: {
                stop = 0;

                break;
            }

            default: {
                break;
            }
        }
    }
}