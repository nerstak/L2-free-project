#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <SDL/SDL.h>

#include "loadingScreen.h"

#include "../window.h"
#include "../asset.h"

/**
 * Global variables (use with caution please)
 */

extern void assets_Scene_loadingScreen(ImageCollector* myImageCollector, bool loadOrUnload) {
    Asset* assetsList = getList_Asset("src/scenes/loadingScreen.kuro");

    if (loadOrUnload == true) {
        loadList_ImageCollector(myImageCollector, assetsList);
    } else {
        unloadList_ImageCollector(myImageCollector, assetsList);
    }

    clean_Asset(&assetsList);
}

extern void eventProcess_Scene_loadingScreen(SDL_Event event) {}

extern void renderScene_Scene_loadingScreen(SDL_Surface* window, ImageCollector* myImageCollector) {
    SDL_Surface* loadingScreenSurface = NULL;
    loadingScreenSurface = getLoadingScreen(myImageCollector);

    SDL_Rect loadingScreenSurfacePos;
    loadingScreenSurfacePos.x = 0;
    loadingScreenSurfacePos.y = 0;

    loadSurface(loadingScreenSurface, window, loadingScreenSurfacePos);

    SDL_FreeSurface(loadingScreenSurface);
}

extern void logicProcess_Scene_loadingScreen() {}

static SDL_Surface* getLoadingScreen(ImageCollector* myImageCollector) {
    SDL_Surface* loadingScreen = NULL;
    loadingScreen = SDL_CreateRGBSurface(SDL_HWSURFACE, 1280, 720, 32, 0, 0, 0, 0);

    return loadingScreen;
}
