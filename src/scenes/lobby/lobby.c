#include "lobby.h"
#include "../../engine/game/plants.h"


extern void assets_Scene_lobby(Engine* engine, Data* data, bool loadOrUnload) {
    char path[] = "src/scenes/lobby/files.asset";
    load_Asset(path, loadOrUnload, engine, data);
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
        data->lobby->actionProcess = NONE;
        data->lobby->cursor = 0;
        data->lobby->timerMessage = init_Timer();
        if(data->Isaac->day == 0) {
            // Display introduction & tutorial
            alterSpeed(data->Isaac, (float) (- data->Isaac->stats->basic->speed * 0.3), 'c');
            data->lobby->tutorial = 1;
            start_Timer(data->lobby->timerMessage);
        } else {
            data->lobby->tutorial = 0;
        }


        data->Isaac->movement->pos->x = 50;
        data->Isaac->movement->pos->y = 384;

        playMusic(engine->soundCollector, "lobby/main_theme");
    } else {
        freeSingleLayout(&(data->lobby->layout));
        free(data->lobby);
        data->lobby = NULL;
    }
}
