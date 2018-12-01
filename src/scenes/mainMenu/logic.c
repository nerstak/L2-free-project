#include "logic.h"
#include "../../game.h"
#include "../../engine/save.h"

static void moveMainMenuSelector(Data* data, int direction);
static void enterMainMenu(Data* data, Engine* engine);
static int getCurrentMainMenuSelector(Data* data);

extern void logicProcess_Scene_mainMenu(Engine* engine, Data* data) {
    if(data->mainMenu->askAction != 5) {
        moveMainMenuSelector(data, data->mainMenu->askAction);
        data->mainMenu->askAction = 0;
    } else {
        data->mainMenu->askAction = 0;
        enterMainMenu(data,engine);
    }
}

static void moveMainMenuSelector(Data* data, int direction) {
    if (direction == -10 && data->mainMenu->position > 0) {
        data->mainMenu->position -= 1;
    } else if (direction == 10 && data->mainMenu->position < 3) {
        data->mainMenu->position += 1;
    }
}

static void enterMainMenu(Data* data, Engine* engine) {
    switch(getCurrentMainMenuSelector(data)) {
        case 0:
            //New game
            if(initGame("", data)) {
                display_SceneCollector(engine,data,"lobby");
            }
            break;
        case 1:
            //Load game
            if(initGame("save1.save", data)) {
                display_SceneCollector(engine,data,"lobby");
            }
            break;
        case 2:
            //Settings, not functional
            display_SceneCollector(engine, data, "options");
            break;
        case 3:
            //Leave game
            data->stop = 0;
        default:
            break;
    }
}

static int getCurrentMainMenuSelector(Data* data) {
    return data->mainMenu->position;
}
