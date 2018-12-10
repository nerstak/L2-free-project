#include "logic.h"
#include "../../engine/game/combat.h"


static bool moveToNewRoom(Engine* engine, Data* data, Coord newCoord);

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
            return true;
        }
    }
    return false;
}

extern void enterdoor(SDL_Rect * door, SDL_Rect * player,dungeonScene_t * room,int direction)
{
    if(BoxCollision(player,door))
    {
        room->moveTo=direction;
    }
}

extern void logicProcess_Scene_dungeon(Engine* engine, Data* data) {
    if (data->dungeonScene->moveTo != -1) {
        switch (data->dungeonScene->moveTo) {
            case 0: {
                Coord newCoord = {data->dungeonScene->currentRoom->coord->x, data->dungeonScene->currentRoom->coord->y - 1};
                if(moveToNewRoom(engine, data, newCoord))
                {
                    data->Isaac->movement->position->x=608;
                    data->Isaac->movement->position->y=505;
                }

                break;
            }

            case 1: {
                Coord newCoord = {data->dungeonScene->currentRoom->coord->x + 1, data->dungeonScene->currentRoom->coord->y};
                if(moveToNewRoom(engine, data, newCoord))
                {
                    data->Isaac->movement->position->x=64;
                    data->Isaac->movement->position->y=262;
                }

                break;
            }

            case 2: {
                Coord newCoord = {data->dungeonScene->currentRoom->coord->x, data->dungeonScene->currentRoom->coord->y + 1};
                if(moveToNewRoom(engine, data, newCoord))
                {
                    data->Isaac->movement->position->x=608;
                    data->Isaac->movement->position->y=10;
                }

                break;
            }

            case 3: {
                Coord newCoord = {data->dungeonScene->currentRoom->coord->x - 1, data->dungeonScene->currentRoom->coord->y};
                if(moveToNewRoom(engine, data, newCoord))
                {
                    data->Isaac->movement->position->x=1152;
                    data->Isaac->movement->position->y=262;
                }

                break;
            }
        }

        data->dungeonScene->moveTo = -1;
    }



    if(data->dungeonScene->askCombat!=-1)
    {
        ProcessCombat(data,&(data->dungeonScene->askCombat));
    }
    else
    {
        data->Isaac->combat->weaponHitBox->x=10000; // clean fix
        data->Isaac->combat->weaponHitBox->y=10000;
        data->Isaac->combat->weaponHitBox->h=0;
        data->Isaac->combat->weaponHitBox->w=0;
    }
    movePlayer_Movement(data, data->dungeonScene->currentRoom->layout->map);


    SDL_Rect door;

    door.h=12;
    door.w=20;
    door.x=630;
    door.y=0;
    enterdoor(&door,data->Isaac->movement->hitBox,data->dungeonScene,0); //UP

    door.y=608;
    enterdoor(&door,data->Isaac->movement->hitBox,data->dungeonScene,2); //DOWN

    door.x=45;
    door.y=342;
    door.h=20;
    door.w=10;
    enterdoor(&door,data->Isaac->movement->hitBox,data->dungeonScene,3); //LEFT

    door.x=1224;
    enterdoor(&door,data->Isaac->movement->hitBox,data->dungeonScene,1); //RIGHT
}

