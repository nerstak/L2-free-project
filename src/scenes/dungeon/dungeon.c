#include <time.h>
#include <dirent.h>

#include "dungeon.h"
#include "../../engine/game/dungeon/generator.h"
#include "../../structures/dungeonScene.h"
#include "../../engine/game/dungeon/roomlist.h"

static void loadDungeonsMap(Engine* engine, Data* data);

extern void assets_Scene_dungeon(Engine* engine, Data* data, bool loadOrUnload) {
    char path[] = "src/scenes/dungeon/files.asset";
    load_Asset(path, loadOrUnload, engine, data);
}

extern void init_Scene_dungeon(Engine* engine, Data* data, bool loadOrUnload) {
    if (loadOrUnload == true) {
        data->dungeonScene = malloc(1 * sizeof(dungeonScene_t));
        if(data->dungeonScene == NULL) {
            exit(EXIT_FAILURE);
        }

        data->dungeonScene->sound = malloc(sizeof(soundDungeon_t));
        if(data->dungeonScene->sound == NULL) {
            exit(EXIT_FAILURE);
        }

        data->dungeonScene->sound->mobsDamaged = initEntitiesBool();
        data->dungeonScene->sound->mobsAttack = initEntitiesBool();
        data->dungeonScene->sound->mobsDisplacement = initEntitiesBool();

        DungeonGenerator* dg = init_DungeonGenerator(time(NULL));

        do {
            generate_DungeonGenerator(dg);
        } while(dg->dungeon == NULL || findStart_Dungeon(dg->dungeon) == NULL);

        data->dungeonScene->dungeon = dg->dungeon;
        data->dungeonScene->currentRoom = findStart_Dungeon(dg->dungeon);
        data->dungeonScene->currentRoom->visited = true;

        clean_DungeonGenerator(&(dg));

        data->dungeonScene->moveTo = -1;

        data->Isaac->movement->position->x=608;
        data->Isaac->movement->position->y=340;
        data->Isaac->movement->direction=0;
        data->dungeonScene->askCombat=-2;

        data->dungeonScene->actionProcess = NONE;

        data->dungeonScene->keyValue = 0;

        data->dungeonScene->sound->bossJustDefeated = 0;
        data->dungeonScene->sound->deathMob = 0;

        data->dungeonScene->notificationQueue = initQueue_Notification();

        data->dungeonScene->pauseBg = SDL_CreateRGBSurface(SDL_HWSURFACE, 1280, 720, 32, 0, 0, 0, 0);

        loadDungeonsMap(engine, data);


        playMusic(engine->soundCollector, "dungeon/main_theme");

        switch(data->field->currentPlant->idVegetable) {
            case 0: {
                data->dungeonScene->dungeonAssets.bg = get_ImageCollector(engine->imageCollector, "dungeon/bgCarrot")->surface;
                data->dungeonScene->dungeonAssets.obstacle = get_ImageCollector(engine->imageCollector, "dungeon/carrotObstacle")->surface;
                data->dungeonScene->dungeonAssets.hole = get_ImageCollector(engine->imageCollector, "dungeon/carrotHole")->surface;
                data->dungeonScene->dungeonAssets.slow = get_ImageCollector(engine->imageCollector, "dungeon/carrotSlow")->surface;

                data->dungeonScene->difficulty = 1.00;

                break;
            }

            case 1: {
                data->dungeonScene->dungeonAssets.bg = get_ImageCollector(engine->imageCollector, "dungeon/bgTomato")->surface;
                data->dungeonScene->dungeonAssets.obstacle = get_ImageCollector(engine->imageCollector, "dungeon/tomatoObstacle")->surface;
                data->dungeonScene->dungeonAssets.hole = get_ImageCollector(engine->imageCollector, "dungeon/tomatoHole")->surface;
                data->dungeonScene->dungeonAssets.slow = get_ImageCollector(engine->imageCollector, "dungeon/tomatoSlow")->surface;

                data->dungeonScene->difficulty = 1.25;

                break;
            }

            case 2: {
                data->dungeonScene->dungeonAssets.bg = get_ImageCollector(engine->imageCollector, "dungeon/bgPotato")->surface;
                data->dungeonScene->dungeonAssets.obstacle = get_ImageCollector(engine->imageCollector, "dungeon/potatoObstacle")->surface;
                data->dungeonScene->dungeonAssets.hole = get_ImageCollector(engine->imageCollector, "dungeon/potatoHole")->surface;
                data->dungeonScene->dungeonAssets.slow = get_ImageCollector(engine->imageCollector, "dungeon/potatoSlow")->surface;

                data->dungeonScene->difficulty = 1.50;

                break;
            }

            case 3: {
                data->dungeonScene->dungeonAssets.bg = get_ImageCollector(engine->imageCollector, "dungeon/bgCorn")->surface;
                data->dungeonScene->dungeonAssets.obstacle = get_ImageCollector(engine->imageCollector, "dungeon/cornObstacle")->surface;
                data->dungeonScene->dungeonAssets.hole = get_ImageCollector(engine->imageCollector, "dungeon/cornHole")->surface;
                data->dungeonScene->dungeonAssets.slow = get_ImageCollector(engine->imageCollector, "dungeon/cornSlow")->surface;

                data->dungeonScene->difficulty = 1.75;

                break;
            }

            case 4: {
                data->dungeonScene->dungeonAssets.bg = get_ImageCollector(engine->imageCollector, "dungeon/bgEggplant")->surface;
                data->dungeonScene->dungeonAssets.obstacle = get_ImageCollector(engine->imageCollector, "dungeon/eggplantObstacle")->surface;
                data->dungeonScene->dungeonAssets.hole = get_ImageCollector(engine->imageCollector, "dungeon/eggplantHole")->surface;
                data->dungeonScene->dungeonAssets.slow = get_ImageCollector(engine->imageCollector, "dungeon/eggplantSlow")->surface;

                data->dungeonScene->difficulty = 2.00;

                break;
            }

            default: {
                // TODO: Error here

                break;
            }
        }
    } else {
        // TODO: Improve that part
        stopMusic();

        // Now we clean all our layouts
        KeyLevelRoomMapping* keylevel = getRooms_Dungeon(data->dungeonScene->dungeon);
        RoomList* rooms = *getRooms_KeyLevelRoomMapping(keylevel, 0);
        RoomList* tempRoom = NULL;
        tempRoom = rooms;

        while (tempRoom != NULL) {
            freeSingle_Layout(&(tempRoom->data->layout));

            tempRoom = tempRoom->next;
        }

        clean_KeyLevelRoomMapping(&(keylevel));

        clean_Dungeon(&(data->dungeonScene->dungeon));

        for (int i = 0; i < (int) data->dungeonScene->layoutsLength; i += 1) {
            free(data->dungeonScene->layoutsPath[i]);
        }
        
        freeEntitiesBool(&data->dungeonScene->sound->mobsDamaged);
        freeEntitiesBool(&data->dungeonScene->sound->mobsAttack);
        freeEntitiesBool(&data->dungeonScene->sound->mobsDisplacement);
        free(data->dungeonScene->sound);
        data->dungeonScene->sound = NULL;

        cleanQueue_Notification(&(data->dungeonScene->notificationQueue));

        SDL_FreeSurface(data->dungeonScene->pauseBg);

        free(data->dungeonScene);
        data->dungeonScene = NULL;
    }
}


static void loadDungeonsMap(Engine* engine, Data* data) {
    struct dirent* de;
    DIR* dr = opendir("./src/data/dungeons");

    if (dr == NULL) {
        printf("An error occured while listing a directory");
        exit(EXIT_FAILURE);
    }

    // Alloc our array of layouts
    data->dungeonScene->layoutsPath = malloc(5 * sizeof(char*));
    int count = 0;
    int i = 0;

    while ((de = readdir(dr)) != NULL) {
        if (de->d_name[0] != '.' && de->d_name[1] != '.') {
            data->dungeonScene->layoutsPath[i] = NULL;
            data->dungeonScene->layoutsPath[i] = malloc(BUFSIZ * sizeof(char));

            if (data->dungeonScene->layoutsPath[i] == NULL) {
                printf("An error occurred while initializing a String object");
                exit(EXIT_FAILURE);
            }

            strcpy(data->dungeonScene->layoutsPath[i], de->d_name);
            char* temp = NULL;
            temp = realloc(data->dungeonScene->layoutsPath[i], (strlen(data->dungeonScene->layoutsPath[i]) + 1) * sizeof(char));

            if (temp == NULL) {
                printf("An error occurred while reallocating a String object");
                exit(EXIT_FAILURE);
            }

            data->dungeonScene->layoutsPath[i] = temp;

            i += 1;
            count += 1;

            if (count == 5) {
                char** temp = NULL;
                temp = realloc(data->dungeonScene->layoutsPath, (i + 5) * sizeof(char*));

                if (temp == NULL) {
                    printf("An error occurred while reallocating a String array");
                    exit(EXIT_FAILURE);
                }

                data->dungeonScene->layoutsPath = temp;
                count = 0;
            }
        }
    }

    char** temp = NULL;
    temp = realloc(data->dungeonScene->layoutsPath, i * sizeof(Layout*));

    if (temp == NULL) {
        printf("An error occurred while reallocating a String array");
        exit(EXIT_FAILURE);
    }

    data->dungeonScene->layoutsPath = temp;
    data->dungeonScene->layoutsLength = (size_t) i;

    // Now we predefine all our layouts
    KeyLevelRoomMapping* keylevel = getRooms_Dungeon(data->dungeonScene->dungeon);
    RoomList* rooms = *getRooms_KeyLevelRoomMapping(keylevel, 0);
    RoomList* tempRoom = NULL;
    tempRoom = rooms;

    while (tempRoom != NULL) {
        if (isStart_Room(tempRoom->data) || isBoss_Room(tempRoom->data) || isGoal_Room(tempRoom->data)) {
            tempRoom->data->layout = loadSingle_Layout("dungeons", data->dungeonScene->layoutsPath[0]);
        } else {
            size_t layoutId = 0;

            while (layoutId == 0) {
                layoutId = rand() % data->dungeonScene->layoutsLength;
            }

            tempRoom->data->layout = loadSingle_Layout("dungeons", data->dungeonScene->layoutsPath[layoutId]);
        }

        tempRoom = tempRoom->next;
    }

    closedir(dr);
}