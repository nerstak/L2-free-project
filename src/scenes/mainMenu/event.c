#include "event.h"

#include "../../utils/enhancedSwitch.h"

extern void eventProcess_Scene_mainMenu(SDL_Event event, Engine* engine, Data* data) {
    if(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN: {
                // Key pressed
                int input = event.key.keysym.sym;

                SWITCH(input)
                    CASE(engine->keys->UP)
                        data->mainMenu->askAction = -10;
                    BREAK

                    CASE(engine->keys->DOWN)
                        data->mainMenu->askAction = 10;
                    BREAK

                    CASE(engine->keys->SELECT)
                        data->mainMenu->askAction = 5;
                    BREAK

                    CASE(SDLK_ESCAPE)
                        data->stop = 0;
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
                data->mainMenu->askAction = 0;
                break;
            }
        }
    }
}
