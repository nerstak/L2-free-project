#include "logic.h"
#include "../../game.h"
#include "../../engine/config.h"

static void moveCursorOptions(Engine* engine, Data* data);

static void preSelect(Engine* engine, Data* data);
static void preSelectFPS(Engine* engine, Data* data);
static void preSelectSound(Engine* engine, Data* data, int actualValue);

static void editValues(Engine* engine, Data* data);
static void editFPS(Engine* engine, Data* data);
static void editSound(Engine* engine, Data* data, char* type);

static void alterKey(Engine* engine, Data* data);


extern void logicProcess_Scene_options(Engine* engine, Data* data) {
    if(data->options->askAction != O_NONE && data->options->askAction != O_LEAVE && data->options->isKeyChanging != 1) {
        moveCursorOptions(engine, data);
    }else if(data->options->isKeyChanging == 1) {
        alterKey(engine, data);
    }else if(data->options->askAction == O_LEAVE) {
        writeConfig(engine);
        if(engine->sceneCollector->previousOverlay == NULL) {
            display_SceneCollector(engine, data, engine->sceneCollector->previousScene->name);
        }else {
            display_SceneCollector(engine, data, engine->sceneCollector->previousOverlay->name);
        }

    }
}

static void moveCursorOptions(Engine* engine, Data* data) {
    switch(data->options->askAction) {
        case O_LEFT: {
            if((data->options->nTypeSelected == 3 && data->options->nSelected % 2 != 0) || (data->options->nSelected > 0 && data->options->nTypeSelected != 3)) {
                (data->options->nSelected)--;
                editValues(engine, data);
            }
            break;
        }
        case O_RIGHT: {
            if ((data->options->nTypeSelected == 3 && data->options->nSelected % 2 != 1) || (data->options->nSelected < 3 && data->options->nTypeSelected != 3)) {
                (data->options->nSelected)++;
                editValues(engine, data);
            }
            break;
        }
        case O_UP: {
            if(data->options->nTypeSelected != 0) {
                if((data->options->nTypeSelected == 3 && data->options->nSelected / 2 == 0) || data->options->nTypeSelected < 3) {
                    (data->options->nTypeSelected)--;
                    preSelect(engine,data);
                } else {
                    (data->options->nSelected) -= 2;
                }

            }
            break;
        }
        case O_DOWN: {
            if(data->options->nTypeSelected != 3) {
                (data->options->nTypeSelected)++;
                preSelect(engine,data);
            } else if(data->options->nSelected / 2 != 5) {
                (data->options->nSelected) += 2;
            }
            break;
        }
        case O_ENTER: {
            if(data->options->nTypeSelected == 3) {
                data->options->isKeyChanging = 1;
            }
            break;
        }
        default:
            break;
    }
    data->options->askAction = O_NONE;
}

static void preSelect(Engine* engine, Data* data) {
    switch(data->options->nTypeSelected) {
        case 0: {
            //FPS
            preSelectFPS(engine,data);
            break;
        }
        case 1: {
            //SFX
            preSelectSound(engine,data,engine->volumeSFX);
            break;
        }
        case 2: {
            //Music
            preSelectSound(engine,data,engine->volumeMusic);
            break;
        }
        case 3: {
            //Keys
            data->options->nSelected = 0;
            break;
        }
        default: {
            break;
        }
    }
}

static void preSelectFPS(Engine* engine, Data* data) {
    switch(getMaxFps_Fps(engine->fps)) {
        case 60: {
            data->options->nSelected = 0;
            break;
        }
        case 120: {
            data->options->nSelected = 1;
            break;
        }
        case 144: {
            data->options->nSelected = 2;
            break;
        }
        default: {
            if(!engine->fps->fpsLimited) {
                data->options->nSelected = 3;
            } else {
                data->options->nSelected = 0;
            }
            break;
        }
    }
}

static void preSelectSound(Engine* engine, Data* data, int actualValue) {
    switch(actualValue) {
        case 0: {
            data->options->nSelected = 0;
            break;
        }
        case 33: {
            data->options->nSelected = 1;
            break;
        }
        case 66: {
            data->options->nSelected = 2;
            break;
        }
        case 100: {
            data->options->nSelected = 3;
            break;
        }
        default: {
            data->options->nSelected = 3;
            break;
        }
    }
}

static void editValues(Engine* engine, Data* data) {
    switch(data->options->nTypeSelected) {
        case 0: {
            //Case FPS
            editFPS(engine, data);
            break;
        }
        case 1: {
            //Case SFX
            editSound(engine,data,"sfx");
            break;
        }
        case 2: {
            //Case Music
            editSound(engine,data,"music");
            break;
        }
        default: {
            break;
        }
    }
}

static void editFPS(Engine* engine, Data* data) {
    switch(data->options->nSelected) {
        case 0: {
            setMaxFps_Fps(engine->fps,true,60);
            break;
        }
        case 1: {
            setMaxFps_Fps(engine->fps,true,120);
            break;
        }
        case 2: {
            setMaxFps_Fps(engine->fps,true,144);
            break;
        }
        case 3: {
            setMaxFps_Fps(engine->fps,true,-1);
            break;
        }
        default: {
            break;
        }
    }
}

static void editSound(Engine* engine, Data* data, char* type) {
    switch(data->options->nSelected) {
        case 0: {
            setVolume(engine, type, 0);
            break;
        }
        case 1: {
            setVolume(engine, type, 33);
            break;
        }
        case 2: {
            setVolume(engine, type, 66);
            break;
        }
        case 3: {
            setVolume(engine, type, 100);
            break;
        }
        default: {
            break;
        }
    }
}

static void alterKey(Engine* engine, Data* data) {
    if(data->options->newKey != -1) {
        alterKeyID(engine->keys, data->options->nSelected, data->options->newKey);
        data->options->newKey = -1;
        data->options->isKeyChanging = 0;
    } else if (data->options->newKey != -1){
        data->options->newKey = -1;
        data->options->isKeyChanging = 0;
    }
    data->options->askAction = O_NONE;
}