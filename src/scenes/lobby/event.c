#include "event.h"

extern void eventProcess_Scene_lobby(SDL_Event event, Engine* engine, Data* data) {
    float Vchange=2*(SDL_GetTicks() - data->Isaac->movement->timesince)*0.06;
    if(Vchange>300)
        Vchange=0;

    Uint8 *keystate = SDL_GetKeyState(NULL);

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
            }
        }
        default:
            if(keystate[SDLK_w]||keystate[SDLK_a]||keystate[SDLK_s]||keystate[SDLK_d])
            {
                if(keystate[SDLK_w])
                    data->Isaac->movement->velocity->y-=Vchange;
                if(keystate[SDLK_a])
                    data->Isaac->movement->velocity->x-=Vchange;
                if(keystate[SDLK_s])
                    data->Isaac->movement->velocity->y+=Vchange;
                if(keystate[SDLK_d])
                    data->Isaac->movement->velocity->x+=Vchange;
            }
    }
}
