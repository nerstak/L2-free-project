#include "render.h"

#include "../../window.h"

static SDL_Surface* getLoadingScreen(ImageCollector* myImageCollector);

static SDL_Surface* getLoadingScreen(ImageCollector* myImageCollector) {
    SDL_Surface* loadingScreen = NULL;
    loadingScreen = SDL_CreateRGBSurface(SDL_HWSURFACE, 1280, 720, 32, 0, 0, 0, 0);

    return loadingScreen;
}

extern void renderScene_Scene_loadingScreen(SDL_Surface* window, Engine* engine, Data* data) {
    SDL_Surface* loadingScreenSurface = NULL;
    loadingScreenSurface = getLoadingScreen(engine->imageCollector);

    SDL_Rect loadingScreenSurfacePos;
    loadingScreenSurfacePos.x = 0;
    loadingScreenSurfacePos.y = 0;

    loadSurface(loadingScreenSurface, window, loadingScreenSurfacePos);

    SDL_FreeSurface(loadingScreenSurface);
}