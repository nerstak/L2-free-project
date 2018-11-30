#include "optionsScreen.h"

extern void assets_Scene_optionsScreen(Engine* engine, Data* data, bool loadOrUnload) {
    Asset* assetsList = getList_Asset("src/scenes/options/files.asset");

    if (loadOrUnload == true) {
        loadList_ImageCollector(engine->imageCollector, assetsList);
    } else {
        unloadList_ImageCollector(engine->imageCollector, assetsList);
    }

    clean_Asset(&assetsList);
}

extern void init_Scene_optionsScreen(Engine* engine, Data* data, bool loadOrUnload) {
    if (loadOrUnload == true) {
        data->options = NULL;
        data->options = malloc(1 * sizeof(options_t));

        if (data->options == NULL) {
            printf("An error occured while initializing a options_t object\n");
            exit(EXIT_FAILURE);
        }

        data->options->askAction = 0;
        data->options->nSelected = 0;
        data->options->nTypeSelected = 0;
    } else {
        free(data->options);
        data->options = NULL;
    }
}
