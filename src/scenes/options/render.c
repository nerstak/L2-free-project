#include "render.h"
#include "../../window.h"

static SDL_Surface* getOptions(ImageCollector* myImageCollector, FontCollector* myFontCollector, Data* data);

static SDL_Surface* getOptions(ImageCollector* myImageCollector, FontCollector* myFontCollector, Data* data) {
    SDL_Surface* options = NULL;
    options = SDL_CreateRGBSurface(SDL_HWSURFACE, 1280, 720, 32, 0, 0, 0, 0);

    //Init surfaces
    SDL_Surface* bg = NULL;
    SDL_Rect bgPos;

    SDL_Surface* selection = NULL;
    SDL_Rect selectionPos;

    bg = get_ImageCollector(myImageCollector, "options/main_bg")->surface;
    selection = get_ImageCollector(myImageCollector, "options/selection")->surface;

    /*
    TTF_Font* font1 = NULL;
    TTF_Font* font2 = NULL;

    font1 = get_FontCollector(myFontCollector, "menu/65")->font;
    font2 = get_FontCollector(myFontCollector, "menu/40")->font;
    SDL_Color black = {0, 0, 0, 0};
    */

    //Background blit
    bgPos.x = 0;
    bgPos.y = 0;

    SDL_BlitSurface(bg, NULL, options, &bgPos);

    //Selection blit
    if(data->options->nTypeSelected != 3) {
        selectionPos.x = 563 + (data->options->nSelected) * 80;
        selectionPos.y = 198 + (data->options->nTypeSelected) * 60;
    } else {
        selectionPos.x = 544 + (data->options->nSelected % 2) * 264;
        selectionPos.y = 414 + (data->options->nSelected / 2) * 40;
    }





    SDL_BlitSurface(selection, NULL, options, &selectionPos);

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