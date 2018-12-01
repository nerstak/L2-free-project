#include "event.h"



extern void eventProcess_Scene_mainMenu(SDL_Event event, Engine* engine, Data* data) {
    if(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN: {
                // Key pressed
                int input = event.key.keysym.sym;

                printf("%s\n",SDL_GetKeyName(input));
                if(input == engine->keys->UP) {
                    data->mainMenu->askAction = -10;
                } else if (input == engine->keys->DOWN) {
                    data->mainMenu->askAction = 10;
                } else if (input == engine->keys->SELECT) {
                    data->mainMenu->askAction = 5;
                } else if (input == SDLK_ESCAPE) {
                    data->stop = 0;
                }

                /*
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
                    case SDLK_ESCAPE:
                        data->stop= 0;
                        break;
                    default:
                        break;
                }*/
                break;
            }
            case SDL_QUIT: {
                    data->stop = 0;
                    break;
            }
            default: {
                data->mainMenu->askAction = 0;
                break;
            }
        }
    }
}
