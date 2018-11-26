#include <time.h>
#include "test.h"
#include "../../dungeon/generator.h"

extern void assets_Scene_test(Engine* engine, Data* data, bool loadOrUnload) {}

extern void init_Scene_test(Engine* engine, Data* data, bool loadOrUnload) {
    DungeonGenerator* dungeonGenerator = init_DungeonGenerator(time(NULL));
    generate_DungeonGenerator(dungeonGenerator);
}
