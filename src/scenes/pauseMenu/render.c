#include "render.h"
#include "../../window.h"


static SDL_Surface* getPauseMenu(ImageCollector* myImageCollector, FontCollector* myFontCollector, Data* data, Engine* engine);

static SDL_Surface* getPauseMenu(ImageCollector* myImageCollector, FontCollector* myFontCollector, Data* data, Engine* engine) {
    SDL_Surface* pauseMenu = NULL;
    pauseMenu = SDL_CreateRGBSurface(SDL_HWSURFACE, 1280, 720, 32, 0, 0, 0, 0);

    //Init surfaces
    SDL_Surface* bg = NULL;
    SDL_Rect bgPos;

    SDL_Surface* bgBlur = NULL;

    SDL_Surface* selection = NULL;
    SDL_Rect selectionPos;

    SDL_Surface* player = NULL;
    SDL_Rect playerPos;


    bg = get_ImageCollector(myImageCollector, "pause/bg")->surface;
    selection = get_ImageCollector(myImageCollector, "pause/cursor")->surface;
    if(strcmp(engine->sceneCollector->previousScene->name,"lobby") == 0) {
        bgBlur = get_ImageCollector(myImageCollector, "pause/lobby_blur")->surface;
        player = get_ImageCollector(myImageCollector, "pause/player_blur")->surface;
    }


    //Background blit
    bgPos.x = 0;
    bgPos.y = 0;

    SDL_BlitSurface(bgBlur, NULL, pauseMenu, &bgPos);

    if(strcmp(engine->sceneCollector->previousScene->name,"lobby") == 0) {
        plantsBlit(pauseMenu, data, myImageCollector, 'b');

        playerPos.x = data->Isaac->movement->position->x;
        playerPos.y = data->Isaac->movement->position->y;
        SDL_BlitSurface(player, data->Isaac->movement->spriteBox, pauseMenu, &playerPos);
    }


    SDL_BlitSurface(bg, NULL, pauseMenu, &bgPos);

    //Selector blit
    selectionPos.x = 490;
    selectionPos.y = 227 + 110 * data->pauseMenu->position;

    SDL_BlitSurface(selection, NULL, pauseMenu, &selectionPos);

    return pauseMenu;

}

extern void renderScene_Scene_pauseMenu(SDL_Surface* window, Engine* engine, Data* data) {
    SDL_Surface* pauseMenuSurface = NULL;
    pauseMenuSurface = getPauseMenu(engine->imageCollector, engine->fontCollector, data, engine);

    SDL_Rect pauseMenuSurfacePos;
    pauseMenuSurfacePos.x = 0;
    pauseMenuSurfacePos.y = 0;

    applySurface_Window(pauseMenuSurface, window, pauseMenuSurfacePos);

    SDL_FreeSurface(pauseMenuSurface);
}