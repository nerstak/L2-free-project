#include "logic.h"
#include "../../engine/game/combat.h"


static bool moveToNewRoom(Engine* engine, Data* data, Coord newCoord);
static void enterDoor(Engine* engine, Data* data, SDL_Rect* door, SDL_Rect* player, dungeonScene_t* room, int direction);

static bool moveToNewRoom(Engine* engine, Data* data, Coord newCoord) {
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

            // We place the entities
            if (newRoom->cleaned == false) {
                for (int i = 0; i < newRoom->layout->lines; i += 1) {
                    for (int j = 0; j < newRoom->layout->columns; j += 1) {
                        printf("%c", newRoom->layout->map[i][j].type);
                        if (newRoom->layout->map[i][j].type == '0' || newRoom->layout->map[i][j].type == '1' || newRoom->layout->map[i][j].type == '2' || newRoom->layout->map[i][j].type == '3') {
                            switch(newRoom->layout->map[i][j].type) {
                                case '0': {
                                    EntityList* e = init_EntityNode(MOTH);
                                    e->data->movement->position->x = 64 * j;
                                    e->data->movement->position->y = 6 + 64 * i;

                                    append_EntityNode(e, &(data->entities));

                                    break;
                                }

                                /*case '1': {
                                    break;
                                }

                                case '2': {
                                    break;
                                }

                                case '3': {
                                    break;
                                }*/

                                default: {
                                    EntityList* e = init_EntityNode(MOTH);
                                    e->data->movement->position->x = 64 * j;
                                    e->data->movement->position->y = 6 + 64 * i;

                                    append_EntityNode(e, &(data->entities));

                                    // TODO: Error
                                }
                            }
                        }
                    }
                    printf("\n");
                }
            }

            return true;
        }
    }
    return false;
}

static void enterDoor(Engine* engine, Data* data, SDL_Rect* door, SDL_Rect* player, dungeonScene_t* room, int direction) {
    if(BoxCollision(player,door) && data->dungeonScene->currentRoom->cleaned == true) {
        room->moveTo=direction;
    }
}

extern void logicProcess_Scene_dungeon(Engine* engine, Data* data) {
    if (data->dungeonScene->actionProcess == NONE) {
        if (data->dungeonScene->moveTo != -1) {
            switch (data->dungeonScene->moveTo) {
                case 0: {
                    Coord newCoord = {data->dungeonScene->currentRoom->coord->x, data->dungeonScene->currentRoom->coord->y - 1};

                    if(moveToNewRoom(engine, data, newCoord)) {
                        data->Isaac->movement->position->x=608;
                        data->Isaac->movement->position->y=505;
                    }

                    break;
                }

                case 1: {
                    Coord newCoord = {data->dungeonScene->currentRoom->coord->x + 1, data->dungeonScene->currentRoom->coord->y};

                    if(moveToNewRoom(engine, data, newCoord)) {
                        data->Isaac->movement->position->x=64;
                        data->Isaac->movement->position->y=262;
                    }

                    break;
                }

                case 2: {
                    Coord newCoord = {data->dungeonScene->currentRoom->coord->x, data->dungeonScene->currentRoom->coord->y + 1};

                    if(moveToNewRoom(engine, data, newCoord)) {
                        data->Isaac->movement->position->x=608;
                        data->Isaac->movement->position->y=6;
                    }

                    break;
                }

                case 3: {
                    Coord newCoord = {data->dungeonScene->currentRoom->coord->x - 1, data->dungeonScene->currentRoom->coord->y};

                    if(moveToNewRoom(engine, data, newCoord)) {
                        data->Isaac->movement->position->x=1152;
                        data->Isaac->movement->position->y=262;
                    }

                    break;
                }
            }

            data->dungeonScene->moveTo = -1;
        }
        if (data->dungeonScene->askCombat != -1) {
            ProcessCombat(data,&(data->dungeonScene->askCombat));
        } else {
            data->Isaac->combat->weaponHitBox->x=10000; // clean fix
            data->Isaac->combat->weaponHitBox->y=10000;
            data->Isaac->combat->weaponHitBox->h=0;
            data->Isaac->combat->weaponHitBox->w=0;
        }

        process_Entity(&(data->entities), data);
        movePlayer_Movement(data, data->dungeonScene->currentRoom->layout->map);

        if (data->entities == NULL && data->dungeonScene->currentRoom->cleaned == false) {
            data->dungeonScene->currentRoom->cleaned = true;
        }

        SDL_Rect door;

        door.h=12;
        door.w=20;
        door.x=630;
        door.y=0;
        enterDoor(engine, data, &door, data->Isaac->movement->hitBox, data->dungeonScene, 0); //UP

        door.y=608;
        enterDoor(engine, data, &door, data->Isaac->movement->hitBox, data->dungeonScene, 2); //DOWN

        door.x=45;
        door.y=342;
        door.h=20;
        door.w=10;
        enterDoor(engine, data, &door, data->Isaac->movement->hitBox, data->dungeonScene, 3); //LEFT

        door.x=1224;
        enterDoor(engine, data, &door, data->Isaac->movement->hitBox, data->dungeonScene, 1); //RIGHT
    } else {
        //TODO: We have to pause every timer of the dungeon
        if (data->dungeonScene->actionProcess == PAUSE) {
            data->dungeonScene->actionProcess = NONE;
            display_SceneCollector(engine, data, "pauseMenu");
        } else if (data->dungeonScene->actionProcess == INVENTORY) {
            data->dungeonScene->actionProcess = NONE;
            display_SceneCollector(engine, data, "inventory");
        }
    }
}

