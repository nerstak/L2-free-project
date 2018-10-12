#include "window.h"

#include <SDL/SDL.h>

extern void initWindow() {
    SDL_Init(SDL_INIT_VIDEO); // We only init VIDEO_mod for now

    SDL_Surface* window = NULL;
    window = SDL_SetVideoMode(1280, 720, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    if (window == NULL) {
        fprintf(stderr, "Failed to load graphical view: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_WM_SetCaption("free_project v0.0.1 Alpha", NULL);

    SDL_Surface* scene = NULL;

    handleWindow();
    SDL_Quit();
}

static void handleWindow() {
    int stop = 1;
    SDL_Event event;

    Uint32 startTime = 0;
    Uint32 endTime = 0;
    Uint32 delta = 0;
    short timePerFrame = 16; // 1/60 approx

    while (stop) {
        while (SDL_PollEvent(&event)) {
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

        if (!startTime) {
            startTime = SDL_GetTicks();
        } else {
            delta = endTime - startTime;
        }

        if (delta < timePerFrame) {
            SDL_Delay(timePerFrame - delta); // We delay if we're a little bit too fast
        }

        startTime = endTime;
        endTime = SDL_GetTicks();
    }
}
