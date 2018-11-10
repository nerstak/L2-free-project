#include "event.h"
#include "../../game.h"

static void moveMainMenuSelector(Data* data, int direction);
static void enterMainMenu(Data* data);
static int getCurrentMainMenuSelector(Data* data);

static void moveMainMenuSelector(Data* data, int direction) {
    if (direction == 0 && data->mainMenu->position > 0) {
        data->mainMenu->position -= 1;
    } else if (direction == 1 && data->mainMenu->position < 3) {
        data->mainMenu->position += 1;
    }
}

static void enterMainMenu(Data* data) {
    printf("Selected: %d\n", data->mainMenu->position);
}

static int getCurrentMainMenuSelector(Data* data) {
    return data->mainMenu->position;
}

extern void eventProcess_Scene_mainMenu(SDL_Event event, Engine* engine, Data* data) {
    switch (event.type) {
        case SDL_KEYDOWN: {
            // Key pressed
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    // Move menu selector
                    // Should be through a call to a function only ! (setter)
                    moveMainMenuSelector(data, 0);
                    break;
                case SDLK_DOWN:
                    // Move menu selector
                    // Should be through a call to a function only ! (setter)
                    moveMainMenuSelector(data, 1);
                    break;
                case SDLK_RETURN:
                    // Select our menu ? For now only
                    enterMainMenu(data);

                    if (getCurrentMainMenuSelector(data) == 3) Game_stop = 0;

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