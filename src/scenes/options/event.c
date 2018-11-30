#include "event.h"



extern void eventProcess_Scene_options(SDL_Event event, Engine* engine, Data* data) {
    if(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN: {
                // Key pressed
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE: {
                        data->options->askAction = O_LEAVE;
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
