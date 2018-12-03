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

        data->lobby->layout = loadSingleLayout("lobby","lobby");
        data->lobby->actualPlant = NULL;
        data->lobby->askAction = 0;
        data->lobby->askCombat = -1;
        data->lobby->actionProcess = NONE;
        data->lobby->counterPressKey = 0;
        data->lobby->counterPressKeyMove = 0;

        //TEMP because theres no monsters in the lobby but I still need to test this shit
        data->monsters=malloc(sizeof(MonsterNode));
        data->monsters->next=NULL;
        data->monsters->monster=malloc(sizeof(Monster));
        data->monsters->monster->movement=malloc(sizeof(MovementValues));
        data->monsters->monster->movement->Hitbox=malloc(sizeof(SDL_Rect));
        data->monsters->monster->movement->SpriteBox=malloc(sizeof(SDL_Rect));
        data->monsters->monster->movement->pos=malloc(sizeof(coordinates_entity));
        data->monsters->monster->movement->velocity=malloc(sizeof(coordinates_entity));

    } else {
        freeSingleLayout(&(data->lobby->layout));
        free(data->lobby);
        data->lobby = NULL;
    }
}
