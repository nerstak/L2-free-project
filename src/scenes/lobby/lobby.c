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

        //TEMP because theres no monsters in the lobby but I still need to test this shit
        data->monsters=malloc(sizeof(MonsterNode));
        data->monsters->next=NULL;
        data->monsters->monster=malloc(sizeof(Monster));
        data->monsters->monster->movement=malloc(sizeof(MovementValues));
        data->monsters->monster->movement->Hitbox=malloc(sizeof(SDL_Rect));
        data->monsters->monster->movement->SpriteBox=malloc(sizeof(SDL_Rect));
        data->monsters->monster->movement->pos=malloc(sizeof(coordinates_entity));
        data->monsters->monster->movement->velocity=malloc(sizeof(coordinates_entity));


        data->monsters->monster->movement->step=0;
        data->monsters->monster->Speed=1;
        data->monsters->monster->type=0;
        data->monsters->monster->movement->pos->x=0;
        data->monsters->monster->movement->pos->y=0;
        data->monsters->monster->movement->Hitbox->h=64;
        data->monsters->monster->movement->Hitbox->w=64;
        data->monsters->monster->movement->velocity->x=0;
        data->monsters->monster->movement->velocity->y=0;
        data->monsters->monster->movement->SpriteBox->h=96;
        data->monsters->monster->movement->SpriteBox->w=128;
        data->monsters->monster->movement->Hitbox->h=96;
        data->monsters->monster->movement->Hitbox->w=64;
        data->monsters->monster->movement->SpriteBox->x=0;
        data->monsters->monster->movement->SpriteBox->y=0;
        data->monsters->monster->Health=1;

        data->lobby->cursor = 0;
        data->lobby->timerMessage = init_Timer();

    } else {
        freeSingleLayout(&(data->lobby->layout));
        free(data->lobby);
        data->lobby = NULL;
    }
}
