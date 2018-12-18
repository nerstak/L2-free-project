#include "mainMenu.h"

extern void assets_Scene_mainMenu(Engine* engine, Data* data, bool loadOrUnload) {
    stopMusic();
    char path[] = "src/scenes/mainMenu/files.asset";
    load_Asset(path, loadOrUnload, engine, data);
}

extern void init_Scene_mainMenu(Engine* engine, Data* data, bool loadOrUnload) {
    if (loadOrUnload == true) {
        data->mainMenu = NULL;
        data->mainMenu = malloc(1 * sizeof(mainMenu_t));

        if (data->mainMenu == NULL) {
            printf("An error occured while initializing a mainMenu_t object\n");
            exit(EXIT_FAILURE);
        }

        data->mainMenu->position = 0;
        data->mainMenu->askAction = 0;

        if(data->Isaac) {
            free_Player(&(data->Isaac));
        }
        if(data->field) {
            freeField(&(data->field));
        }
        if(data->referenceItems) {
            freeReference(&(data->referenceItems));
        }

        playMusic(engine->soundCollector, "menu/main_theme");
    } else {
        free(data->mainMenu);
        data->mainMenu = NULL;
    }
}
