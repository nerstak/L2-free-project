#include "event.h"

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