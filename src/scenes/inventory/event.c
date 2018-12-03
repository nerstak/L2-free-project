#include "event.h"

#include "../../utils/enhancedSwitch.h"

extern void eventProcess_Scene_inventory(SDL_Event event, Engine* engine, Data* data) {
    if(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN: {
                // Key pressed
                int input = event.key.keysym.sym;

                SWITCH(input)
                    CASE(engine->keys->UP_ATTACK)
                        data->inventory->askAction = I_UP;
                    BREAK

                    CASE(engine->keys->DOWN_ATTACK)
                        data->inventory->askAction = I_DOWN;
                    BREAK

                    CASE(engine->keys->LEFT_ATTACK)
                        data->inventory->askAction = I_LEFT;
                    BREAK

                    CASE(engine->keys->RIGHT_ATTACK)
                        data->inventory->askAction = I_RIGHT;
                    BREAK

                    CASE(engine->keys->SELECT)
                        data->inventory->askAction = I_ENTER;
                    BREAK

                    CASE(engine->keys->DELETE)
                        data->inventory->askAction = I_DELETE;
                    BREAK

                    CASE(SDLK_ESCAPE)
                        data->inventory->askAction = I_LEAVE;
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
