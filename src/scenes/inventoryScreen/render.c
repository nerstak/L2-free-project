#include "render.h"
#include "../../window.h"

static SDL_Surface* getInventory(ImageCollector* myImageCollector, FontCollector* myFontCollector, Data* data);

static SDL_Surface* getInventory(ImageCollector* myImageCollector, FontCollector* myFontCollector, Data* data) {
    SDL_Surface* inventory = NULL;
    inventory = SDL_CreateRGBSurface(SDL_HWSURFACE, 1280, 720, 32, 0, 0, 0, 0);

    SDL_Surface* bg = NULL;
    SDL_Rect bgPos;

    bgPos.x = 0;
    bgPos.y = 0;

    bg = get_ImageCollector(myImageCollector, "inventory/interface")->surface;

    SDL_BlitSurface(bg, NULL, inventory, &bgPos);

    return inventory;
}

extern void renderScene_Scene_inventory(SDL_Surface* window, Engine* engine, Data* data) {
    SDL_Surface* mainInventorySurface = NULL;
    mainInventorySurface = getInventory(engine->imageCollector, engine->fontCollector, data);

    SDL_Rect mainInventorySurfacePos;
    mainInventorySurfacePos.x = 0;
    mainInventorySurfacePos.y = 0;

    loadSurface(mainInventorySurface, window, mainInventorySurfacePos);

    SDL_FreeSurface(mainInventorySurface);
}