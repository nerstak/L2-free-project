#include "event.h"

extern void eventProcess_Scene_dungeon(SDL_Event event, Engine* engine, Data* data) {
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN: {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE: {
                        data->stop = 0;
                        break;
                    }

                    case SDLK_KP_PLUS: {
                        alterHealth(data->Isaac, 1.5, 'c');
                        break;
                    }

                    case SDLK_KP_MINUS: {
                        alterHealth(data->Isaac, (float) -1.5, 'c');
                        break;
                    }

                    default: {
                        break;
                    }
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
