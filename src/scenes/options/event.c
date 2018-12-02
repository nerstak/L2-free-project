#include "event.h"

#include "../../utils/enhancedSwitch.h"



extern void eventProcess_Scene_options(SDL_Event event, Engine* engine, Data* data) {
    if(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN: {
                // Key pressed
                int input = event.key.keysym.sym;
                if(data->options->isKeyChanging == 1) {
                    data->options->newKey = input;
                }
                SWITCH(input)
                    CASE(SDLK_ESCAPE)
                        data->options->askAction = O_LEAVE;
                    BREAK

                    CASE(engine->keys->LEFT_ATTACK)
                        data->options->askAction = O_LEFT;
                    BREAK

                    CASE(engine->keys->RIGHT_ATTACK)
                        data->options->askAction = O_RIGHT;
                    BREAK

                    CASE(engine->keys->UP_ATTACK)
                        data->options->askAction = O_UP;
                    BREAK

                    CASE(engine->keys->DOWN_ATTACK)
                        data->options->askAction = O_DOWN;
                    BREAK

                    CASE(engine->keys->SELECT)
                        data->options->askAction = O_ENTER;
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
