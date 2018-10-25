#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <SDL/SDL.h>

#include "lobby.h"

#include "../window.h"
#include "../asset.h"
#include "../data.h"
#include "../player.h"

static SDL_Surface* getLobby(ImageCollector* myImageCollector);

extern void assets_Scene_lobby(ImageCollector* myImageCollector, bool loadOrUnload) {
    Asset* assetsList = getList_Asset("src/scenes/lobby.asset");

    if (loadOrUnload == true) {
        loadList_ImageCollector(myImageCollector, assetsList);
    } else {
        unloadList_ImageCollector(myImageCollector, assetsList);
    }

    clean_Asset(&assetsList);
}

extern void init_Scene_lobby(Data* data, bool loadOrUnload) {
    if (loadOrUnload == true) {
        // We init datas
    } else {
        // We free it
    }
}

extern void eventProcess_Scene_lobby(SDL_Event event, Data* data) {
    switch (event.type) {
        case SDL_KEYDOWN: {
            // Key pressed
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    // Move up player, has to be implemented
                    break;
                case SDLK_DOWN:
                    // Move down player, has to be implemented
                    break;
                case SDLK_RIGHT:
                    // Move right player, has to be implemented
                    break;
                case SDLK_LEFT:
                    // Move left player, has to be implemented
                    break;
                case SDLK_SPACE:
                    //Interact with shop or garden, has to be implemented
                    break;
                case SDLK_RETURN:
                    // Inventory?
                    break;
                default: {
                    break;
                }
            }
        }
    }
}

extern void renderScene_Scene_lobby(SDL_Surface* window, ImageCollector* myImageCollector, Data* data) {
    SDL_Surface* lobbySurface = NULL;
    lobbySurface = getLobby(myImageCollector);

    SDL_Rect lobbySurfacePos;
    lobbySurfacePos.x = 0;
    lobbySurfacePos.y = 0;

    loadSurface(lobbySurface, window, lobbySurfacePos);

    SDL_FreeSurface(lobbySurface);
}

extern void logicProcess_Scene_lobby(Data* data) {
    player_logic_lobby(data);
}

static SDL_Surface* getLobby(ImageCollector* myImageCollector) {
    SDL_Surface* lobbySurface = NULL;
    lobbySurface = SDL_CreateRGBSurface(SDL_HWSURFACE, 1280, 720, 32, 0, 0, 0, 0);

    return lobbySurface;
}
