#include "event.h"

extern void eventProcess_Scene_lobby(SDL_Event event, Engine* engine, Data* data) {
    float Vchange=2*(SDL_GetTicks() - data->Isaac->movement->timesince)*0.06;
    if(Vchange>300)
        Vchange=0;

    if(data->Isaac->combat->step>450)
    {
        data->Isaac->combat->step=0;
        data->Isaac->movement->direction=data->lobby->askCombat;
        data->lobby->askCombat = -1;
    }

    Uint8 *keystate = SDL_GetKeyState(NULL);

    if(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN: {
                // Key pressed
                switch (event.key.keysym.sym) {
                    case SDLK_UP: {
                        if(data->lobby->askCombat==-1)
                        {
                            data->lobby->askCombat = 1;
                        }
                        break;
                    }
                    case SDLK_DOWN: {
                        if(data->lobby->askCombat==-1)
                            data->lobby->askCombat = 0;
                        break;
                    }
                    case SDLK_RIGHT: {
                        if(data->lobby->askCombat==-1)
                            data->lobby->askCombat = 2;

                        data->lobby->counterPressKeyMove = 3;
                        break;
                    }
                    case SDLK_LEFT: {
                        if(data->lobby->askCombat==-1)
                            data->lobby->askCombat = 3;

                        data->lobby->counterPressKeyMove = -3;
                        break;
                    }
                    case SDLK_e: {
                        data->lobby->actionProcess = INVENTORY;
                        break;
                    }
                    case SDLK_RETURN:
                        data->lobby->counterPressKey = 3;
                        break;
                    case SDLK_ESCAPE:
                        data->stop= 0;
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
           // data->lobby->counterPressKeyMove = -3;
        }
        if(keystate[SDLK_s]) {
            data->Isaac->movement->velocity->y += Vchange;
        }
        if(keystate[SDLK_d]) {
            data->Isaac->movement->velocity->x+=Vchange;
           // data->lobby->counterPressKeyMove = 3;
        }
    }
}
