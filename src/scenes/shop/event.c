#include "event.h"
#include "../../utils/enhancedSwitch.h"

extern void eventProcess_Scene_shop(SDL_Event event, Engine* engine, Data* data) {
    if(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN: {
                // Key pressed
                int input = event.key.keysym.sym;

                SWITCH(input)
                CASE(engine->keys->UP_ATTACK)
                data->shop->askAction = I_UP;
                BREAK

                CASE(engine->keys->DOWN_ATTACK)
                data->shop->askAction = I_DOWN;
                BREAK

                CASE(engine->keys->LEFT_ATTACK)
                data->shop->askAction = I_LEFT;
                BREAK

                CASE(engine->keys->RIGHT_ATTACK)
                data->shop->askAction = I_RIGHT;
                BREAK

                CASE(engine->keys->SELECT)
                data->shop->askAction = I_ENTER;
                BREAK

                CASE(SDLK_BACKSPACE)
                data->shop->askAction = I_DELETE;
                BREAK

                CASE(SDLK_ESCAPE)
                data->shop->askAction = I_LEAVE;
                BREAK
                ENDSWITCH

                break;
            }
            case SDL_QUIT: {
                data->stop = 0;
                break;
            }
            default: {
                break;
            }
        }
    }
}