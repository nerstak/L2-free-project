#include "event.h"

extern void eventProcess_Scene_lobby(SDL_Event event, Engine* engine, Data* data) {
    float Vchange=2*(SDL_GetTicks() - data->Isaac->movement->timesince)*0.06;
    if(Vchange>300)
        Vchange=0;

    Uint8 *keystate = SDL_GetKeyState(NULL);

    if(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN: {
                // Key pressed
                switch (event.key.keysym.sym) {
                    case SDLK_e: {
                        data->lobby->actionProcess = INVENTORY;
                        break;
                    }
                    case SDLK_SPACE:
                        //Interact with shop or garden, has to be implemented
                        break;
                    case SDLK_RETURN:
                        data->lobby->counterPressKey = 3;
                        break;
                    case SDLK_ESCAPE:
                        data->stop= 0;
                        break;
                    case SDLK_UNDERSCORE:
                        data->lobby->actionProcess = 10;
                        break;
                    default:
                        break;
                }
                break;
            }
            case SDL_QUIT: {
                    data->stop = 0;
                    break;
            }
            default:
                break;
        }
    }
    
    if(keystate[SDLK_w] || keystate[SDLK_a] || keystate[SDLK_s] || keystate[SDLK_d]) {
        if(keystate[SDLK_w]) {
            data->Isaac->movement->velocity->y -= Vchange;
        }
        if(keystate[SDLK_a]) {
            data->Isaac->movement->velocity->x-=Vchange;
            data->lobby->counterPressKeyMove = -3;
        }
        if(keystate[SDLK_s]) {
            data->Isaac->movement->velocity->y += Vchange;
        }
        if(keystate[SDLK_d]) {
            data->Isaac->movement->velocity->x+=Vchange;
            data->lobby->counterPressKeyMove = 3;
        }
    }
}
