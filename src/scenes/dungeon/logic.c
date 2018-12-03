#include "logic.h"

static void moveToNewRoom(Engine* engine, Data* data, Coord newCoord);

static void moveToNewRoom(Engine* engine, Data* data, Coord newCoord) {
    TreeMapNode* node = NULL;
    node = get_TreeMap(data->dungeonScene->dungeon->rooms, &newCoord);

    if (node != NULL) {
        Room* newRoom = node->value;
        bool found = false;

        for (int i = 0; i < (int) data->dungeonScene->currentRoom->childrenLength; i += 1) {
            if (data->dungeonScene->currentRoom->children[i] == newRoom) {
                found = true;
            }
        }

        if (getParent_Room(data->dungeonScene->currentRoom) == newRoom) {
            found = true;
        }

        if (found == true) {
            // We move to the room
            newRoom->visited = true;
            data->dungeonScene->currentRoom = newRoom;
        }
    }
}

extern void logicProcess_Scene_dungeon(Engine* engine, Data* data) {
    if (data->dungeonScene->moveTo != -1) {
        switch (data->dungeonScene->moveTo) {
            case 0: {
                Coord newCoord = {data->dungeonScene->currentRoom->coord->x, data->dungeonScene->currentRoom->coord->y - 1};
                moveToNewRoom(engine, data, newCoord);

                break;
            }

            case 1: {
                Coord newCoord = {data->dungeonScene->currentRoom->coord->x + 1, data->dungeonScene->currentRoom->coord->y};
                moveToNewRoom(engine, data, newCoord);

                break;
            }

            case 2: {
                Coord newCoord = {data->dungeonScene->currentRoom->coord->x, data->dungeonScene->currentRoom->coord->y + 1};
                moveToNewRoom(engine, data, newCoord);

                break;
            }

            case 3: {
                Coord newCoord = {data->dungeonScene->currentRoom->coord->x - 1, data->dungeonScene->currentRoom->coord->y};
                moveToNewRoom(engine, data, newCoord);

                break;
            }
        }

        data->dungeonScene->moveTo = -1;
    }
}