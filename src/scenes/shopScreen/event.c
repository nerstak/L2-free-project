#include "event.h"

extern void eventProcess_Scene_shop(SDL_Event event, Engine* engine, Data* data) {
    if(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN: {
                // Key pressed
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        data->shop->askAction = I_UP;
                        break;
                    case SDLK_DOWN:
                        data->shop->askAction = I_DOWN;
                        break;
                    case SDLK_LEFT:
                        data->shop->askAction = I_LEFT;
                        break;
                    case SDLK_RIGHT:
                        data->shop->askAction = I_RIGHT;
                        break;
                    case SDLK_RETURN:
                        data->shop->askAction = I_ENTER;
                        break;
                    case SDLK_ESCAPE:
                        data->shop->askAction = I_LEAVE;
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
