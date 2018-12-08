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

                    case SDLK_UP: {
                        data->dungeonScene->moveTo = 0;
                        break;
                    }

                    case SDLK_RIGHT: {
                        data->dungeonScene->moveTo = 1;
                        break;
                    }

                    case SDLK_DOWN: {
                        data->dungeonScene->moveTo = 2;
                        break;
                    }

                    case SDLK_LEFT: {
                        data->dungeonScene->moveTo = 3;
                        break;
                    }

                    case SDLK_KP_PLUS: {
                        alterHealth_Player(data->Isaac, 1.5, 'c');
                        break;
                    }

                    case SDLK_KP_MINUS: {
                        alterHealth_Player(data->Isaac, (float) -1.5, 'c');
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
