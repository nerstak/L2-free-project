#include "window.h"

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

#include "game.h"

SDL_Surface* window = NULL;

static void clean_Window();

extern void init_Window() {
    // Initialization of all modules required
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    TTF_Init();
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);

    // Creating our window
    window = SDL_SetVideoMode(1280, 720, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    if (window == NULL) {
        fprintf(stderr, "Failed to load graphical view: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Apply settings to our window
    SDL_WM_SetCaption("free_project v0.0.1 Super Alpha", NULL);

    // Launch our game
    gameLoop(window);

    // Cleaning our window
    clean_Window();

    // Closing all modules launched
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
}

static void clean_Window() {
    SDL_FreeSurface(window);
}

extern void renderScreen() {
    // We flip the screen
    SDL_Flip(window);

    // Then we prepare it for the next iteration
    SDL_FillRect(window, &window->clip_rect, SDL_MapRGB(window->format, 0, 0, 0));
}

extern void applySurface_Window(SDL_Surface* src, SDL_Surface* dest, SDL_Rect offset) {
    SDL_BlitSurface(src, NULL, dest, &offset);
}
