#include "render.h"

#include "../../window.h"

static SDL_Surface* getLobby(ImageCollector* myImageCollector);

static SDL_Surface* getLobby(ImageCollector* myImageCollector) {
    SDL_Surface* lobbySurface = NULL;
    lobbySurface = SDL_CreateRGBSurface(SDL_HWSURFACE, 1280, 720, 32, 0, 0, 0, 0);

    return lobbySurface;
}

extern void renderScene_Scene_lobby(SDL_Surface* window, ImageCollector* myImageCollector, FontCollector* myFontCollector, Data* data) {
    SDL_Surface* lobbySurface = NULL;
    lobbySurface = getLobby(myImageCollector);

    SDL_Rect lobbySurfacePos;
    lobbySurfacePos.x = 0;
    lobbySurfacePos.y = 0;

    loadSurface(lobbySurface, window, lobbySurfacePos);

    SDL_FreeSurface(lobbySurface);
}