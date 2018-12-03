#include "event.h"
#include "../../utils/enhancedSwitch.h"

extern void eventProcess_Scene_lobby(SDL_Event event, Engine* engine, Data* data) {
    float Vchange=2*(SDL_GetTicks() - data->Isaac->movement->timesince)*0.06;
    if(Vchange>300)
        Vchange=0;

    Uint8 *keystate = SDL_GetKeyState(NULL);

    if(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN: {
                // Key pressed
                int input = event.key.keysym.sym;
                SWITCH(input)
                    CASE(engine->keys->INVENTORY)
                        data->lobby->askAction = INVENTORY;
                    BREAK

                    CASE(engine->keys->SELECT)
                        data->lobby->askAction = SELECT;
                    BREAK
                    
                    CASE(engine->keys->LEFT)
                        data->lobby->askAction = LEFT;
                    BREAK
                    
                    CASE(engine->keys->RIGHT)
                        data->lobby->askAction = RIGHT;
                    BREAK

                    CASE(SDLK_ESCAPE)
                        data->lobby->actionProcess = PAUSE;
                    BREAK
                ENDSWITCH

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
   
    if(keystate[engine->keys->UP] || keystate[engine->keys->LEFT] || keystate[engine->keys->DOWN] || keystate[engine->keys->RIGHT]) {
        if(keystate[engine->keys->UP]) {
            data->Isaac->movement->velocity->y -= Vchange;
        }
        if(keystate[engine->keys->LEFT]) {
            data->Isaac->movement->velocity->x-=Vchange;
        }
        if(keystate[engine->keys->DOWN]) {
            data->Isaac->movement->velocity->y += Vchange;
        }
        if(keystate[engine->keys->RIGHT]) {
            data->Isaac->movement->velocity->x+=Vchange;
        }
    }
}
