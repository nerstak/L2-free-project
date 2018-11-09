#include "event.h"

extern void eventProcess_Scene_shop(SDL_Event event, Data* data) {
    switch (event.type) {
        case SDL_KEYDOWN: {
            // Key pressed
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    data->shop->ask_action = -10;
                    break;
                case SDLK_DOWN:
                    data->shop->ask_action = 10;
                    break;
                case SDLK_LEFT:
                    data->shop->ask_action = -1;
                    break;
                case SDLK_RIGHT:
                    data->shop->ask_action = 1;
                    break;
                case SDLK_RETURN:
                    data->shop->ask_action = 5;
                    break;
                default: {

                    break;
                }
            }

            break;
        }

        default: {
            data->shop->ask_action = 0;
            break;
        }
    }
}