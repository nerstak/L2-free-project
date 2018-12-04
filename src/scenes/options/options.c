#include "options.h"

extern void assets_Scene_options(Engine* engine, Data* data, bool loadOrUnload) {
    Asset* assetsList = getList_Asset("src/scenes/options/files.asset");

    if (loadOrUnload == true) {
        loadList_ImageCollector(engine->imageCollector, assetsList);
    } else {
        unloadList_ImageCollector(engine->imageCollector, assetsList);
    }

    clean_Asset(&assetsList);
}

extern void init_Scene_options(Engine* engine, Data* data, bool loadOrUnload) {
    if (loadOrUnload == true) {
        data->options = NULL;
        data->options = malloc(1 * sizeof(options_t));

        if (data->options == NULL) {
            printf("An error occured while initializing a options_t object\n");
            exit(EXIT_FAILURE);
        }
        data->options->askAction = O_NONE;
        data->options->isKeyChanging = 0;
        data->options->newKey = -1;
        data->options->nTypeSelected = 0;

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

    } else {
        free(data->options);
        data->options = NULL;
    }
}
