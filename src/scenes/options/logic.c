#include "logic.h"
#include "../../game.h"
#include "../../engine/save.h"


extern void logicProcess_Scene_options(Engine* engine, Data* data) {
    if(data->options->askAction == O_LEAVE) {
        display_SceneCollector(engine, data, "mainMenu");
    }
}