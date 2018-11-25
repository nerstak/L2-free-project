#include "event.h"

extern void eventProcess_Scene_shop(SDL_Event event, Engine* engine, Data* data) {
    if(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN: {
                // Key pressed
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        data->shop->askAction = -10;
                        break;
                    case SDLK_DOWN:
                        data->shop->askAction = 10;
                        break;
                    case SDLK_LEFT:
                        data->shop->askAction = -1;
                        break;
                    case SDLK_RIGHT:
                        data->shop->askAction = 1;
                        break;
                    case SDLK_RETURN:
                        data->shop->askAction = 5;
                        break;
                    case SDLK_ESCAPE:
                        data->stop= 0;
                        break;
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
                //data->shop->askAction = 0;
                break;
            }
        }
    }
}
