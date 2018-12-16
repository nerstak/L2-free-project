#include "window.h"

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>

#include "game.h"

SDL_Surface* window = NULL;

static void clean_Window();

extern void init_Window() {
    // Initialization of all modules required
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    TTF_Init();
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    Mix_AllocateChannels(10);

    // Creating our window
    window = SDL_SetVideoMode(1280, 720, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    if (window == NULL) {
        fprintf(stderr, "Failed to load graphical view: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Apply settings to our window
    SDL_WM_SetCaption("Stardew of Isaac - Alpha Release 1.0", NULL);

    // Apply icon to our game
    SDL_Surface* icon = IMG_Load("src/resources/gfx/icon.png");
    SDL_WM_SetIcon(icon, NULL);

    // Launch our game
    gameLoop(window);

    // Cleaning our window
    clean_Window();
    SDL_FreeSurface(icon);

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
