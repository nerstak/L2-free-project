#include <stdio.h>
#include <SDL/SDL_video.h>
#include <SDL/SDL_image.h>

#include "window.h"
#include "menu.h"

int position = 0;

extern void displayMainMenu(SDL_Surface* window) {
    SDL_Surface* mainMenuSurface = NULL;
    mainMenuSurface = getMainMenu();

    SDL_Rect mainMenuSurfacePos;
    mainMenuSurfacePos.x = (window->w / 2) - (mainMenuSurface->w / 2);
    mainMenuSurfacePos.y = (window->h / 2) - (mainMenuSurface->h / 2);

    loadSurface(mainMenuSurface, window, mainMenuSurfacePos);

    SDL_FreeSurface(mainMenuSurface);
}

extern void moveMainMenuSelector(int direction) {
    if (direction == 0 && position > 0) {
        position -= 1;
    } else if (direction == 1 && position < 2) {
        position += 1;
    } else {
        // Rip ?
    }
}

extern void enterMainMenu() {
    printf("Selected: %d\n", position);
}

extern int getCurrentMainMenuSelector() {
    return position;
}

static SDL_Surface* getMainMenu() {
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

    logo = IMG_Load("../src/gfx/menu/main_logo.jpg");

    newGameBtn = IMG_Load("../src/gfx/menu/main_button.jpg");
    loadGameBtn = IMG_Load("../src/gfx/menu/main_button.jpg");
    exitBtn = IMG_Load("../src/gfx/menu/main_button.jpg");

    selector = IMG_Load("../src/gfx/menu/select.png");

    logoPos.x = (mainMenu->w / 2) - (logo->w / 2);
    logoPos.y = 10;

    newGameBtnPos.x = (mainMenu->w / 2) - (newGameBtn->w / 2);
    newGameBtnPos.y = 300;

    loadGameBtnPos.x = (mainMenu->w / 2) - (loadGameBtn->w / 2);
    loadGameBtnPos.y = 400;

    exitGameBtnPos.x = (mainMenu->w / 2) - (exitBtn->w / 2);
    exitGameBtnPos.y = 500;

    selectorPos.x = (mainMenu->w / 2) - (newGameBtn->w / 2);
    selectorPos.y = 330 + (position) * 100;

    SDL_BlitSurface(newGameBtn, NULL, mainMenu, &newGameBtnPos);
    SDL_BlitSurface(loadGameBtn, NULL, mainMenu, &loadGameBtnPos);
    SDL_BlitSurface(exitBtn, NULL, mainMenu, &exitGameBtnPos);
    SDL_BlitSurface(logo, NULL, mainMenu, &logoPos);
    SDL_BlitSurface(selector, NULL, mainMenu, &selectorPos);

    SDL_FreeSurface(newGameBtn);
    SDL_FreeSurface(loadGameBtn);
    SDL_FreeSurface(exitBtn);
    SDL_FreeSurface(logo);
    SDL_FreeSurface(selector);

    return mainMenu;
}