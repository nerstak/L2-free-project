#include "event.h"

extern void eventProcess_Scene_lobby(SDL_Event event, Engine* engine, Data* data) {
    switch (event.type) {
        case SDL_KEYDOWN: {
            // Key pressed
            switch (event.key.keysym.sym) {
                case SDLK_SPACE:
                    //Interact with shop or garden, has to be implemented
                    break;
                case SDLK_RETURN:
                    // Inventory?
                    break;
                default:
                    if(keystate[SDLK_w])
                        data->Isaac->movement->velocity->y-=2;
                    if(keystate[SDLK_a])
                        data->Isaac->movement->velocity->x-=2;
                    if(keystate[SDLK_s])
                        data->Isaac->movement->velocity->y+=2;
                    if(keystate[SDLK_d])
                        data->Isaac->movement->velocity->x+=2;
            }
        }
    }
}
