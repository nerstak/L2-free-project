#include "event.h"



extern void eventProcess_Scene_mainMenu(SDL_Event event, Engine* engine, Data* data) {
    switch (event.type) {
        case SDL_KEYDOWN: {
            // Key pressed
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    data->mainMenu->askAction = -10;
                    break;
                case SDLK_DOWN:
                    data->mainMenu->askAction = 10;
                    break;
                case SDLK_RETURN:
                    data->mainMenu->askAction = 5;
                    break;
                default: {
                    break;
                }
            }

            break;
        }

        default: {
            data->mainMenu->askAction = 0;
            break;
        }
    }
}