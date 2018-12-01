#include "render.h"
#include "../../window.h"

static SDL_Surface* getOptions(ImageCollector* myImageCollector, FontCollector* myFontCollector, Data* data);

static SDL_Surface* getOptions(ImageCollector* myImageCollector, FontCollector* myFontCollector, Data* data) {
    SDL_Surface* options = NULL;
    options = SDL_CreateRGBSurface(SDL_HWSURFACE, 1280, 720, 32, 0, 0, 0, 0);

    SDL_Surface* bg = NULL;

    /*
    TTF_Font* font1 = NULL;
    TTF_Font* font2 = NULL;

    font1 = get_FontCollector(myFontCollector, "menu/65")->font;
    font2 = get_FontCollector(myFontCollector, "menu/40")->font;
    SDL_Color black = {0, 0, 0, 0};
    */

    SDL_Rect bgPos;

    bg = get_ImageCollector(myImageCollector, "options/main_bg")->surface;

    bgPos.x = 0;
    bgPos.y = 0;

    SDL_BlitSurface(bg, NULL, options, &bgPos);

    return options;
}

extern void renderScene_Scene_options(SDL_Surface* window, Engine* engine, Data* data) {
    SDL_Surface* optionsSurface = NULL;
    optionsSurface = getOptions(engine->imageCollector, engine->fontCollector, data);

    SDL_Rect optionsSurfacePos;
    optionsSurfacePos.x = 0;
    optionsSurfacePos.y = 0;

    applySurface_Window(optionsSurface, window, optionsSurfacePos);

    SDL_FreeSurface(optionsSurface);
}