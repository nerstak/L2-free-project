#include "render.h"
#include "../../window.h"

static SDL_Surface* getOptionsScreen(ImageCollector* myImageCollector, FontCollector* myFontCollector, Data* data);

static SDL_Surface* getOptionsScreen(ImageCollector* myImageCollector, FontCollector* myFontCollector, Data* data) {
    SDL_Surface* options = NULL;
    options = SDL_CreateRGBSurface(SDL_HWSURFACE, 1280, 720, 32, 0, 0, 0, 0);

    SDL_Surface* bg = NULL;

    TTF_Font* font1 = NULL;
    TTF_Font* font2 = NULL;

    font1 = get_FontCollector(myFontCollector, "menu/65")->font;
    font2 = get_FontCollector(myFontCollector, "menu/40")->font;
    SDL_Color black = {0, 0, 0, 0};

    SDL_Rect bgPos;

    bg = get_ImageCollector(myImageCollector, "options/main_bg")->surface;

    bgPos.x = 0;
    bgPos.y = 0;

    SDL_BlitSurface(bg, NULL, options, &bgPos);

    return options;
}

extern void renderScene_Scene_optionsScreen(SDL_Surface* window, Engine* engine, Data* data) {
    SDL_Surface* optionsScreenSurface = NULL;
    optionsScreenSurface = getOptionsScreen(engine->imageCollector, engine->fontCollector, data);

    SDL_Rect optionsScreenSurfacePos;
    optionsScreenSurfacePos.x = 0;
    optionsScreenSurfacePos.y = 0;

    applySurface_Window(optionsScreenSurface, window, optionsScreenSurfacePos);

    SDL_FreeSurface(optionsScreenSurface);
}