#include "event.h"

#include "../../utils/enhancedSwitch.h"

extern void eventProcess_Scene_pauseMenu(SDL_Event event, Engine* engine, Data* data) {
    if(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN: {
                // Key pressed
                int input = event.key.keysym.sym;

                SWITCH(input)
                CASE(engine->keys->UP_ATTACK)
                    data->pauseMenu->askAction = -10;
                BREAK

                CASE(engine->keys->DOWN_ATTACK)
                    data->pauseMenu->askAction = 10;
                BREAK

                CASE(engine->keys->SELECT)
                    data->pauseMenu->askAction = 5;
                BREAK

                CASE(SDLK_ESCAPE)
                    data->pauseMenu->backGame = 1;
                BREAK;

                DEFAULT

                        BREAK_DEFAULT;
                ENDSWITCH

                break;
            }
            case SDL_QUIT: {
                data->stop = 0;
                break;
            }
            default: {
                data->pauseMenu->askAction = 0;
                break;
            }
        }
    }
}