#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "mainMenu.h"

#include "../game.h"
#include "../image.h"
#include "../window.h"
#include "../data.h"

static SDL_Surface* getMainMenu(ImageCollector* myImageCollector, Data* data);

static void moveMainMenuSelector(Data* data, int direction);
static void enterMainMenu(Data* data);
static int getCurrentMainMenuSelector(Data* data);

extern void assets_Scene_mainMenu(ImageCollector* myImageCollector, bool loadOrUnload) {
    Asset* assetsList = getList_Asset("src/scenes/mainMenu.asset");

    if (loadOrUnload == true) {
        loadList_ImageCollector(myImageCollector, assetsList);
    } else {
        unloadList_ImageCollector(myImageCollector, assetsList);
    }

    clean_Asset(&assetsList);
}

extern void init_Scene_mainMenu(Data* data, bool loadOrUnload) {
    if (loadOrUnload == true) {
        data->mainMenu = NULL;
        data->mainMenu = malloc(1 * sizeof(mainMenu_t));

        if (data->mainMenu == NULL) {
            printf("An error occured while initializing a mainMenu_t object\n");
            exit(EXIT_FAILURE);
        }

        data->mainMenu->position = 0;
    } else {
        free(data->mainMenu);
        data->mainMenu = NULL;
    }
}

extern void eventProcess_Scene_mainMenu(SDL_Event event, Data* data) {
    switch (event.type) {
        case SDL_KEYDOWN: {
            // Key pressed
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    // Move menu selector
                    // Should be through a call to a function only ! (setter)
                    moveMainMenuSelector(data, 0);
                    break;
                case SDLK_DOWN:
                    // Move menu selector
                    // Should be through a call to a function only ! (setter)
                    moveMainMenuSelector(data, 1);
                    break;
                case SDLK_RETURN:
                    // Select our menu ? For now only
                    enterMainMenu(data);

                    if (getCurrentMainMenuSelector(data) == 3) Game_stop = 0;

                    break;
                default: {
                    break;
                }
            }

            break;
        }

        default: {
            break;
        }
    }
}

extern void renderScene_Scene_mainMenu(SDL_Surface* window, ImageCollector* myImageCollector, Data* data) {
    SDL_Surface* mainMenuSurface = NULL;
    mainMenuSurface = getMainMenu(myImageCollector, data);

    SDL_Rect mainMenuSurfacePos;
    mainMenuSurfacePos.x = 0;
    mainMenuSurfacePos.y = 0;

    loadSurface(mainMenuSurface, window, mainMenuSurfacePos);

    SDL_FreeSurface(mainMenuSurface);
}

extern void logicProcess_Scene_mainMenu(Data* data) {}

static SDL_Surface* getMainMenu(ImageCollector* myImageCollector, Data* data) {
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

    font1 = TTF_OpenFont("src/fonts/menu.ttf", 65);
    font2 = TTF_OpenFont("src/fonts/menu.ttf", 40);
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

    TTF_CloseFont(font1);
    TTF_CloseFont(font2);

    return mainMenu;
}

static void moveMainMenuSelector(Data* data, int direction) {
    if (direction == 0 && data->mainMenu->position > 0) {
        data->mainMenu->position -= 1;
    } else if (direction == 1 && data->mainMenu->position < 3) {
        data->mainMenu->position += 1;
    }
}

static void enterMainMenu(Data* data) {
    printf("Selected: %d\n", data->mainMenu->position);
}

static int getCurrentMainMenuSelector(Data* data) {
    return data->mainMenu->position;
}