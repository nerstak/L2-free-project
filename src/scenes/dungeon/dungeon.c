#include <time.h>
#include "dungeon.h"
#include "../../engine/game/dungeon/generator.h"
#include "../../structures/dungeonScene.h"

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
        generate_DungeonGenerator(dg);
        data->dungeonScene->dungeon = dg->dungeon; // TODO: Should check that dungeon return smth
        data->dungeonScene->currentRoom = findStart_Dungeon(dg->dungeon);
        data->dungeonScene->currentRoom->visited = true;
        clean_DungeonGenerator(&(dg));
        data->dungeonScene->moveTo = -1;
    } else {
        // TODO: Improve that part
        clean_Dungeon(&(data->dungeonScene->dungeon));
        free(&(data->dungeonScene));
        data->dungeonScene = NULL;
    }
}