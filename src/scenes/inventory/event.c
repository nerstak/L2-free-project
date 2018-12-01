#include "event.h"

extern void eventProcess_Scene_inventory(SDL_Event event, Engine* engine, Data* data) {
    if(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN: {
                // Key pressed
                switch (event.key.keysym.sym) {
                    case SDLK_UP: {
                        data->inventory->askAction = I_UP;
                        break;
                    }
                    case SDLK_DOWN: {
                        data->inventory->askAction = I_DOWN;
                        break;
                    }
                    case SDLK_LEFT: {
                        data->inventory->askAction = I_LEFT;
                        break;
                    }
                    case SDLK_RIGHT: {
                        data->inventory->askAction = I_RIGHT;
                        break;
                    }
                    case SDLK_RETURN: {
                        data->inventory->askAction = I_ENTER;
                        break;
                    }
                    case SDLK_BACKSPACE: {
                        data->inventory->askAction = I_DELETE;
                        break;
                    }
                    case SDLK_ESCAPE: {
                        data->inventory->askAction = I_LEAVE;
                        break;
                    }
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
