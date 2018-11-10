#include "render.h"

static SDL_Surface* getMainMenu(ImageCollector* myImageCollector, FontCollector* myFontCollector, Data* data);

static SDL_Surface* getMainMenu(ImageCollector* myImageCollector, FontCollector* myFontCollector, Data* data) {
    SDL_Surface* mainMenu = NULL;
    mainMenu = SDL_CreateRGBSurface(SDL_HWSURFACE, 1280, 720, 32, 0, 0, 0, 0);

    SDL_Surface* bg = NULL;

    SDL_Surface* newGameBtn = NULL;
    SDL_Surface* loadGameBtn = NULL;
    SDL_Surface* settingsBtn = NULL;
    SDL_Surface* exitBtn = NULL;

    SDL_Surface* selector = NULL;

    TTF_Font* font1 = NULL;
    TTF_Font* font2 = NULL;

    font1 = get_FontCollector(myFontCollector, "menu/65")->font;
    font2 = get_FontCollector(myFontCollector, "menu/40")->font;
    SDL_Color black = {0, 0, 0, 0};

    SDL_Rect bgPos;

    SDL_Rect newGameBtnPos;
    SDL_Rect loadGameBtnPos;
    SDL_Rect settingsPos;
    SDL_Rect exitGameBtnPos;

    SDL_Rect selectorPos;

    bg = get_ImageCollector(myImageCollector, "menu/main_bg")->surface;

    newGameBtn = TTF_RenderText_Solid(font1, "New Game", black);
    loadGameBtn = TTF_RenderText_Solid(font1, "Resume Game", black);
    settingsBtn = TTF_RenderText_Solid(font1, "Settings", black);
    exitBtn = TTF_RenderText_Solid(font2, "Exit", black);

    bgPos.x = 0;
    bgPos.y = 0;

    newGameBtnPos.x = 500;
    newGameBtnPos.y = 345;

    loadGameBtnPos.x = 460;
    loadGameBtnPos.y = 450;

    settingsPos.x = 530;
    settingsPos.y = 540;

    exitGameBtnPos.x = 600;
    exitGameBtnPos.y= 650;

    if (data->mainMenu->position == 3) {
        selectorPos.x = 544;
        selectorPos.y = 645;
        selector = get_ImageCollector(myImageCollector, "menu/main_cursorSingle")->surface;
    } else {
        selectorPos.x = 380;
        selectorPos.y = 350 + (data->mainMenu->position) * 100;
        selector = get_ImageCollector(myImageCollector, "menu/main_cursorDouble")->surface;
    }

    SDL_BlitSurface(bg, NULL, mainMenu, &bgPos);

    SDL_BlitSurface(newGameBtn, NULL, mainMenu, &newGameBtnPos);
    SDL_BlitSurface(loadGameBtn, NULL, mainMenu, &loadGameBtnPos);
    SDL_BlitSurface(settingsBtn, NULL, mainMenu, &settingsPos);
    SDL_BlitSurface(exitBtn, NULL, mainMenu, &exitGameBtnPos);
    SDL_BlitSurface(selector, NULL, mainMenu, &selectorPos);

    SDL_FreeSurface(newGameBtn);
    SDL_FreeSurface(loadGameBtn);
    SDL_FreeSurface(settingsBtn);
    SDL_FreeSurface(exitBtn);

    return mainMenu;
}

extern void renderScene_Scene_mainMenu(SDL_Surface* window, Engine* engine, Data* data) {
    SDL_Surface* mainMenuSurface = NULL;
    mainMenuSurface = getMainMenu(engine->imageCollector, engine->fontCollector, data);

    SDL_Rect mainMenuSurfacePos;
    mainMenuSurfacePos.x = 0;
    mainMenuSurfacePos.y = 0;

    loadSurface(mainMenuSurface, window, mainMenuSurfacePos);

    SDL_FreeSurface(mainMenuSurface);
}