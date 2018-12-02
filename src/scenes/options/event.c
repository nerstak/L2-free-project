#include "event.h"



extern void eventProcess_Scene_options(SDL_Event event, Engine* engine, Data* data) {
    if(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN: {
                // Key pressed
                int input = event.key.keysym.sym;
                if(data->options->isKeyChanging == 1) {
                    data->options->newKey = input;
                }
                switch (input) {
                    case SDLK_ESCAPE: {
                        data->options->askAction = O_LEAVE;
                        break;
                    }
                    case SDLK_LEFT: {
                        data->options->askAction = O_LEFT;
                        break;
                    }
                    case SDLK_RIGHT: {
                        data->options->askAction = O_RIGHT;
                        break;
                    }
                    case SDLK_UP: {
                        data->options->askAction = O_UP;
                        break;
                    }
                    case SDLK_DOWN: {
                        data->options->askAction = O_DOWN;
                        break;
                    }
                    case SDLK_RETURN: {
                        data->options->askAction = O_ENTER;
                        break;
                    }
                    default:
                        break;
                }
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
