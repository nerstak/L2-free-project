#include "logic.h"
#include "../../game.h"
#include "../../engine/save.h"

static void moveCursorOptions(Data* data);

extern void logicProcess_Scene_options(Engine* engine, Data* data) {
    if(data->options->askAction != O_NONE && data->options->askAction != O_LEAVE) {
        moveCursorOptions(data);
    }else if(data->options->askAction == O_LEAVE) {
        display_SceneCollector(engine, data, "mainMenu");
    }
}

static void moveCursorOptions(Data* data) {
    switch(data->options->askAction) {
        case O_LEFT: {
            if(data->options->nSelected > 0) {
                (data->options->nSelected)--;
            }
            break;
        }
        case O_RIGHT: {
            if ((data->options->nTypeSelected == 3 && data->options->nSelected == 0) || (data->options->nSelected < 3 && data->options->nTypeSelected != 3)) {
                (data->options->nSelected)++;
            }
            break;
        }
        case O_UP: {
            if(data->options->nTypeSelected != 0) {
                (data->options->nTypeSelected)--;
            }
            break;
        }
        case O_DOWN: {
            if(data->options->nTypeSelected != 3) {
                (data->options->nTypeSelected)++;
            }
            break;
        }
        default:
            break;
    }
    data->options->askAction = O_NONE;
}