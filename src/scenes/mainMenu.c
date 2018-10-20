#include <SDL/SDL.h>

#include "mainMenu.h"

#include "../game.h"
#include "../image.h"
#include "../window.h"

/**
 * Global variables (use with caution please)
 */
int Scene_mainMenu_position = 0;

extern void assets_Scene_mainMenu(ImageCollector* myImageCollector, bool loadOrUnload) {
    Asset* assetsList = getList_Asset("src/scenes/mainMenu.kuro");

    if (loadOrUnload == true) {
        loadList_ImageCollector(myImageCollector, assetsList);
    } else {
        unloadList_ImageCollector(myImageCollector, assetsList);
    }

    clean_Asset(&assetsList);
}

extern void eventProcess_Scene_mainMenu(SDL_Event event) {
    switch (event.type) {
        case SDL_KEYDOWN: {
            // Key pressed
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    // Move menu selector
                    // Should be through a call to a function only ! (setter)
                    moveMainMenuSelector(0);
                    break;
                case SDLK_DOWN:
                    // Move menu selector
                    // Should be through a call to a function only ! (setter)
                    moveMainMenuSelector(1);
                    break;
                case SDLK_RETURN:
                    // Select our menu ? For now only
                    enterMainMenu();

                    if (getCurrentMainMenuSelector() == 2) Game_stop = 0;

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

extern void renderScene_Scene_mainMenu(SDL_Surface* window, ImageCollector* myImageCollector) {
    SDL_Surface* mainMenuSurface = NULL;
    mainMenuSurface = getMainMenu(myImageCollector);

    SDL_Rect mainMenuSurfacePos;
    mainMenuSurfacePos.x = (window->w / 2) - (mainMenuSurface->w / 2);
    mainMenuSurfacePos.y = (window->h / 2) - (mainMenuSurface->h / 2);

    loadSurface(mainMenuSurface, window, mainMenuSurfacePos);

    SDL_FreeSurface(mainMenuSurface);
}

extern void logicProcess_Scene_mainMenu() {}

static SDL_Surface* getMainMenu(ImageCollector* myImageCollector) {
    SDL_Surface* mainMenu = NULL;
    mainMenu = SDL_CreateRGBSurface(SDL_HWSURFACE, 500, 600, 32, 0, 0, 0, 0);

    SDL_Surface* logo = NULL;

    SDL_Surface* newGameBtn = NULL;
    SDL_Surface* loadGameBtn = NULL;
    SDL_Surface* exitBtn = NULL;

    SDL_Surface* selector = NULL;

    SDL_Rect logoPos;

    SDL_Rect newGameBtnPos;
    SDL_Rect loadGameBtnPos;
    SDL_Rect exitGameBtnPos;

    SDL_Rect selectorPos;

    logo = get_ImageCollector(myImageCollector, "menu/main_logo")->surface;

    newGameBtn = get_ImageCollector(myImageCollector, "menu/main_button")->surface;
    loadGameBtn = get_ImageCollector(myImageCollector, "menu/main_button")->surface;
    exitBtn = get_ImageCollector(myImageCollector, "menu/main_button")->surface;

    selector = get_ImageCollector(myImageCollector, "menu/select")->surface;

    logoPos.x = (mainMenu->w / 2) - (logo->w / 2);
    logoPos.y = 10;

    newGameBtnPos.x = (mainMenu->w / 2) - (newGameBtn->w / 2);
    newGameBtnPos.y = 300;

    loadGameBtnPos.x = (mainMenu->w / 2) - (loadGameBtn->w / 2);
    loadGameBtnPos.y = 400;

    exitGameBtnPos.x = (mainMenu->w / 2) - (exitBtn->w / 2);
    exitGameBtnPos.y = 500;

    selectorPos.x = (mainMenu->w / 2) - (newGameBtn->w / 2);
    selectorPos.y = 330 + (Scene_mainMenu_position) * 100;

    SDL_BlitSurface(newGameBtn, NULL, mainMenu, &newGameBtnPos);
    SDL_BlitSurface(loadGameBtn, NULL, mainMenu, &loadGameBtnPos);
    SDL_BlitSurface(exitBtn, NULL, mainMenu, &exitGameBtnPos);
    SDL_BlitSurface(logo, NULL, mainMenu, &logoPos);
    SDL_BlitSurface(selector, NULL, mainMenu, &selectorPos);

    return mainMenu;
}

static void moveMainMenuSelector(int direction) {
    if (direction == 0 && Scene_mainMenu_position > 0) {
        Scene_mainMenu_position -= 1;
    } else if (direction == 1 && Scene_mainMenu_position < 2) {
        Scene_mainMenu_position += 1;
    }
}

static void enterMainMenu() {
    printf("Selected: %d\n", Scene_mainMenu_position);
}

static int getCurrentMainMenuSelector() {
    return Scene_mainMenu_position;
}