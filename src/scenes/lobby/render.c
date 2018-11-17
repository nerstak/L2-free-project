#include "render.h"
#include "../../window.h"

static SDL_Surface* getLobby(ImageCollector* myImageCollector);

static SDL_Surface* getLobby(ImageCollector* myImageCollector) {
    SDL_Surface* lobbySurface = NULL;
    lobbySurface = SDL_CreateRGBSurface(SDL_HWSURFACE, 1280, 720, 32, 0, 0, 0, 0);

    SDL_Surface* bg = NULL;

    SDL_Rect bgPos;

    bg = get_ImageCollector(myImageCollector, "lobby/bg")->surface;

    bgPos.x = 0;
    bgPos.y = 0;

    SDL_BlitSurface(bg, NULL, lobbySurface, &bgPos);

    return lobbySurface;
}

extern void renderScene_Scene_lobby(SDL_Surface* window, Engine* engine, Data* data) {
    SDL_Surface* lobbySurface = NULL;
    lobbySurface = getLobby(engine->imageCollector);

    SDL_Rect lobbySurfacePos;
    lobbySurfacePos.x = 0;
    lobbySurfacePos.y = 0;

    loadSurface(lobbySurface, window, lobbySurfacePos);

    SDL_FreeSurface(lobbySurface);
}