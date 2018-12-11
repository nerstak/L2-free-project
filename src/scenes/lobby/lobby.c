#include "lobby.h"
#include "../../engine/game/plants.h"


extern void assets_Scene_lobby(Engine* engine, Data* data, bool loadOrUnload) {
    Asset* assetsList = getList_Asset("src/scenes/lobby/files.asset");

    if (loadOrUnload == true) {
        loadList_ImageCollector(engine->imageCollector, assetsList);
    } else {
        unloadList_ImageCollector(engine->imageCollector, assetsList);
    }

    clean_Asset(&assetsList);
}

extern void init_Scene_lobby(Engine* engine, Data* data, bool loadOrUnload) {
    if (loadOrUnload == true) {
        data->lobby = NULL;
        data->lobby = malloc(1 * sizeof(lobby_t));

        if(data->lobby == NULL) {
            printf("An error occured while initializing a lobby_t object\n");
            exit(EXIT_FAILURE);
        }

        data->lobby->layout = loadSingle_Layout("lobby", "lobby");
        data->lobby->actualPlant = NULL;
        data->lobby->askAction = 0;
        data->lobby->askCombat = -1;
        data->lobby->actionProcess = NONE;

        data->lobby->cursor = 0;
        data->lobby->timerMessage = init_Timer();

    } else {
        freeSingle_Layout(&(data->lobby->layout));
        cleanList_Entity(&(data->entities));
        free(data->lobby);
        data->lobby = NULL;
    }
}
