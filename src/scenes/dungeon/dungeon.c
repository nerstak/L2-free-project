#include <time.h>
#include <dirent.h>

#include "dungeon.h"
#include "../../engine/game/dungeon/generator.h"
#include "../../structures/dungeonScene.h"
#include "../../engine/game/dungeon/roomlist.h"

static void loadDungeonsMap(Engine* engine, Data* data);

extern void assets_Scene_dungeon(Engine* engine, Data* data, bool loadOrUnload) {
    Asset* assetsList = getList_Asset("src/scenes/dungeon/files.asset");

    if (loadOrUnload == true) {
        loadList_ImageCollector(engine->imageCollector, assetsList);
    } else {
        unloadList_ImageCollector(engine->imageCollector, assetsList);
    }

    clean_Asset(&assetsList);
}

extern void init_Scene_dungeon(Engine* engine, Data* data, bool loadOrUnload) {
    if (loadOrUnload == true) {
        data->dungeonScene = malloc(1 * sizeof(dungeonScene_t));

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
        data->Isaac->movement->position->y=6;
        data->Isaac->movement->direction=0;
        data->dungeonScene->askCombat=-2;

        loadDungeonsMap(engine, data);

        append_EntityNode(init_EntityNode(MOTH),&(data->entities));
    } else {
        // TODO: Improve that part
        clean_Dungeon(&(data->dungeonScene->dungeon));
        free(&(data->dungeonScene));
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
        size_t layoutId = rand() % data->dungeonScene->layoutsLength;
        tempRoom->data->layout = loadSingle_Layout("dungeons", data->dungeonScene->layoutsPath[layoutId]);

        tempRoom = tempRoom->next;
    }

    closedir(dr);
}