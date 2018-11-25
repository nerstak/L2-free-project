#include "event.h"

extern void eventProcess_Scene_inventory(SDL_Event event, Engine* engine, Data* data) {
    if(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN: {
                // Key pressed
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        data->inventory->askAction = -10;
                        break;
                    case SDLK_DOWN:
                        data->inventory->askAction = 10;
                        break;
                    case SDLK_LEFT:
                        data->inventory->askAction = -1;
                        break;
                    case SDLK_RIGHT:
                        data->inventory->askAction = 1;
                        break;
                    case SDLK_RETURN:
                        data->inventory->askAction = 5;
                        break;
                    case SDLK_BACKSPACE:
                        data->inventory->askAction = 8;
                        break;
                    default: {

                        break;
                    }
                }

                break;
            }

            default: {
                break;
            }
        }
    }
}
