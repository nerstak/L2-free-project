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

        // TEMP because theres no monsters in the lobby but I still need to test this shit

        data->entities = NULL;
        append_EntityNode(init_EntityNode(MOTH),&data->entities);

        data->dyingEntities=NULL;

        data->entities->data->movement->animationStep = 0;
        data->entities->data->speed = 1;
        data->entities->data->type = 0;
        data->entities->data->movement->position->x = 0;
        data->entities->data->movement->position->y = 0;
        data->entities->data->movement->velocity->x = 0;
        data->entities->data->movement->velocity->y = 0;
        data->entities->data->movement->spriteBox->h = 96;
        data->entities->data->movement->spriteBox->w = 128;
        data->entities->data->movement->hitBox->h = 96;
        data->entities->data->movement->hitBox->w = 32;
        data->entities->data->movement->spriteBox->x = 0;
        data->entities->data->movement->spriteBox->y = 0;
        data->entities->data->health = 5;


        data->entities->data->movement->timeSince = init_Timer();

        data->entities->data->attackTimer=init_Timer();

        data->lobby->cursor = 0;
        data->lobby->timerMessage = init_Timer();

    } else {
        freeSingle_Layout(&(data->lobby->layout));
        cleanList_Entity(&(data->entities));
        free(data->lobby);
        data->lobby = NULL;
    }
}
