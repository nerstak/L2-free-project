#include "logic.h"


static void moveCursor(Engine* engine, Data* data);

extern void logicProcess_Scene_pauseMenu(Engine* engine, Data* data) {
    if(data->pauseMenu->askAction != 5 && data->pauseMenu->backGame != 1) {
        moveCursor(engine, data);
        data->pauseMenu->askAction = 0;
    }else{
        if(data->pauseMenu->position == 0 || data->pauseMenu->backGame == 1) {
            playEffect(engine->soundCollector, "loading/leave_menu",0 );
            if(strcmp(engine->sceneCollector->previousScene->name, "dungeon") == 0) {
                unpauseTimer_entities(data->entities);
            }
            display_SceneCollector(engine, data, engine->sceneCollector->previousScene->name);
        } else if (data->pauseMenu->position == 1) {
            data->pauseMenu->askAction = 0;
            playEffect(engine->soundCollector, "pause/confirm_button",0);
            display_SceneCollector(engine, data, "options");
        } else if (data->pauseMenu->position == 2) {
            playEffect(engine->soundCollector, "loading/leave_menu",0);
            display_SceneCollector(engine, data, "mainMenu");
        }
    }
}

static void moveCursor(Engine* engine, Data* data) {
    switch(data->pauseMenu->askAction) {
        case -10: {
            if(data->pauseMenu->position != 0) {
                data->pauseMenu->position--;
                playEffect(engine->soundCollector, "pause/move_button",0);
            }
            break;
        }
        case 10: {
            if(data->pauseMenu->position != 2) {
                data->pauseMenu->position++;
                playEffect(engine->soundCollector, "pause/move_button",0);
            }
            break;
        }
        default:
            break;
    }
}