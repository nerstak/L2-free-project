#include "render.h"
#include "../../engine/game/dungeon/dungeon.h"
#include "../../engine/game/dungeon/roomlist.h"
#include "constants.h"

static void renderBackground(SDL_Surface* window, Engine* engine, Data* data);
static void renderDoors(SDL_Surface* window, Engine* engine, Data* data);
static void renderDoor(SDL_Surface* window, Engine* engine, Data* data, int direction);

static void renderUI(SDL_Surface* window, Engine* engine, Data* data);
static SDL_Surface* renderLifebar(Engine* engine, Data* data);
static void renderKeys(SDL_Surface* window, Engine* engine, Data* data);
static void renderMap(SDL_Surface* window, Engine* engine, Data* data);
static void renderMapDoor(SDL_Surface* window, Engine* engine, Data* data, SDL_Rect origin, int direction);

static void renderBackground(SDL_Surface* window, Engine* engine, Data* data) {
    SDL_Surface* background = get_ImageCollector(engine->imageCollector, "dungeon/bgTomato")->surface;

    SDL_Rect background_Pos;
    background_Pos.x = BG_OFFSET_X;
    background_Pos.y = BG_OFFSET_Y;

    SDL_BlitSurface(background, NULL, window, &background_Pos);

    for (int i = 0; i < data->dungeonScene->currentRoom->layout->lines; i += 1) {
        for (int j = 0; j < data->dungeonScene->currentRoom->layout->columns; j += 1) {
            Tiles temp = data->dungeonScene->currentRoom->layout->map[i][j];

            SDL_Surface* toBlit = NULL;
            SDL_Rect toBlit_Pos;
            toBlit_Pos.x = (Sint16) (j * 64);
            toBlit_Pos.y = (Sint16) (8 + i * 64);

            switch(temp.type) {
                case 'B': {
                    toBlit = get_ImageCollector(engine->imageCollector, "dungeon/tomatoObstacle")->surface;
                    break;
                }

                case 'J': {
                    toBlit = get_ImageCollector(engine->imageCollector, "dungeon/tomatoSlow")->surface;
                    break;
                }

                case 'H': {
                    toBlit = get_ImageCollector(engine->imageCollector, "dungeon/tomatoHole")->surface;
                    break;
                }

                default: {
                    break;
                }
            }

            SDL_BlitSurface(toBlit, NULL, window, &toBlit_Pos);
        }
    }

    renderDoors(window, engine, data);

    SDL_Surface* PlayerSprite=NULL;
    SDL_Rect playerPos;

    playerPos.x=data->Isaac->movement->position->x;
    playerPos.y=data->Isaac->movement->position->y;

    PlayerSprite = get_ImageCollector(engine->imageCollector, "dungeon/player")->surface;

    bool invisible=false;

    if(data->Isaac->invulnerabilityTimer->started)
    {
        if((getTicks_Timer(data->Isaac->invulnerabilityTimer)%100)<50)
        {
            invisible=true;
        }
    }

    if(!invisible)
    {
        /*if (data->lobby->askCombat != -1) {
            playerPos.y -= 32;
            playerPos.x -= 64;

            SDL_BlitSurface(FightSprite, data->Isaac->combat->spriteBox, lobbySurface, &playerPos);
        } else {*/
            SDL_BlitSurface(PlayerSprite, data->Isaac->movement->spriteBox, window, &playerPos);
        //}
    }
    SDL_Surface * Hibox= get_ImageCollector(engine->imageCollector, "dungeon/hibox")->surface;



    /* see door hitboxes for debugging
    SDL_BlitSurface(Hibox,data->Isaac->movement->hitBox , window, data->Isaac->movement->hitBox);

    SDL_Rect doorup,doordown,doorright,doorleft;
    doorup.h=12;
    doorup.w=20;
    doorup.x=630;
    doorup.y=0;

    doordown=doorup;
    doordown.y=608;

    doorleft.x=45;
    doorleft.y=342;
    doorleft.h=20;
    doorleft.w=10;

    doorright=doorleft;
    doorright.x=1224;

    SDL_BlitSurface(Hibox,&doordown , window, &doordown);
    SDL_BlitSurface(Hibox,&doorup , window, &doorup);
    SDL_BlitSurface(Hibox,&doorleft , window, &doorleft);
    SDL_BlitSurface(Hibox,&doorright , window, &doorright);*/
}

static void renderDoors(SDL_Surface* window, Engine* engine, Data* data) {
    for (int i = 0; i < (int) data->dungeonScene->currentRoom->childrenLength; i += 1) {
        int direction = getDirectionTo_Coord(data->dungeonScene->currentRoom->children[i]->coord, data->dungeonScene->currentRoom->coord)->code;
        renderDoor(window, engine, data, direction);
    }

    if (getParent_Room(data->dungeonScene->currentRoom) != NULL) {
        int direction = getDirectionTo_Coord(data->dungeonScene->currentRoom->parent->coord, data->dungeonScene->currentRoom->coord)->code;
        renderDoor(window, engine, data, direction);
    }
}

static void renderDoor(SDL_Surface* window, Engine* engine, Data* data, int direction) {
    SDL_Surface* doors = get_ImageCollector(engine->imageCollector, "dungeon/tomatoDoors")->surface;

    switch (direction) {
        case NORTH: {
            SDL_Rect door_Pos;
            SDL_Rect door_Offset;

            door_Offset.x = 0;
            door_Offset.y = 0;
            door_Offset.w = 172;
            door_Offset.h = 109;

            door_Pos.x = (Sint16) ((window->w / 2) -  door_Offset.w / 2);
            door_Pos.y = 8;

            SDL_BlitSurface(doors, &door_Offset, window, &door_Pos);

            break;
        }

        case EAST: {
            SDL_Rect door_Pos;
            SDL_Rect door_Offset;

            door_Offset.x = 172;
            door_Offset.y = 0;
            door_Offset.w = 109;
            door_Offset.h = 172;

            door_Pos.x = (Sint16) ((window->w) -  door_Offset.w);
            door_Pos.y = (Sint16) ((window->h / 2) - door_Offset.h / 2);

            SDL_BlitSurface(doors, &door_Offset, window, &door_Pos);

            break;
        }

        case SOUTH: {
            SDL_Rect door_Pos;
            SDL_Rect door_Offset;

            door_Offset.x = 0;
            door_Offset.y = 109;
            door_Offset.w = 172;
            door_Offset.h = 109;

            door_Pos.x = (Sint16) ((window->w / 2) -  door_Offset.w / 2);
            door_Pos.y = (Sint16) ((window->h - 8) - door_Offset.h);

            SDL_BlitSurface(doors, &door_Offset, window, &door_Pos);

            break;
        }

        case WEST: {
            SDL_Rect door_Pos;
            SDL_Rect door_Offset;

            door_Offset.x = 281;
            door_Offset.y = 0;
            door_Offset.w = 109;
            door_Offset.h = 172;

            door_Pos.x = (Sint16) (0);
            door_Pos.y = (Sint16) ((window->h / 2) - door_Offset.h / 2);

            SDL_BlitSurface(doors, &door_Offset, window, &door_Pos);

            break;
        }

        default: {
            break;
        }
    }
}


static void renderUI(SDL_Surface* window, Engine* engine, Data* data) {
    SDL_Surface* uiPlayer = NULL;

    if (data->Isaac->stats->current->health == 0) {
        uiPlayer = get_ImageCollector(engine->imageCollector, "dungeon/uiPlayerDead")->surface;
    } else {
        uiPlayer = get_ImageCollector(engine->imageCollector, "dungeon/uiPlayer")->surface;
    }

    SDL_Surface* uiLifebarBg = get_ImageCollector(engine->imageCollector, "dungeon/uiLifebarBg")->surface;
    SDL_Surface* uiLifebar = renderLifebar(engine, data);
    SDL_Surface* mapBG = get_ImageCollector(engine->imageCollector, "dungeon/mapBg")->surface;

    SDL_Rect uiPlayer_Pos;
    uiPlayer_Pos.x = UI_PLAYER_X;
    uiPlayer_Pos.y = UI_PLAYER_Y;
    SDL_Rect uiLifebarBg_Pos;
    uiLifebarBg_Pos.x = UI_LIFEBAR_BG_X;
    uiLifebarBg_Pos.y = UI_LIFEBAR_BG_Y;
    SDL_Rect uiLifebar_Pos;
    uiLifebar_Pos.x = UI_LIFEBAR_X;
    uiLifebar_Pos.y = UI_LIFEBAR_Y;
    SDL_Rect mapBG_Pos;
    mapBG_Pos.x = UI_MAP_BG_X;
    mapBG_Pos.y = UI_MAP_BG_Y;

    SDL_BlitSurface(uiPlayer, NULL, window, &uiPlayer_Pos);
    SDL_BlitSurface(uiLifebarBg, NULL, window, &uiLifebarBg_Pos);
    SDL_BlitSurface(uiLifebar, NULL, window, &uiLifebar_Pos);
    SDL_BlitSurface(mapBG, NULL, window, &mapBG_Pos);

    renderKeys(window, engine, data);

    SDL_FreeSurface(uiLifebar);
}

static SDL_Surface* renderLifebar(Engine* engine, Data* data) {
    SDL_Surface* result = SDL_CreateRGBSurface(SDL_HWSURFACE, UI_LIFEBAR_W, UI_LIFEBAR_H, 32, 0, 0, 0, 0);

    float percentLife = (data->Isaac->stats->current->health / data->Isaac->stats->basic->health) * 100;
    float divPerPercent = (float) UI_LIFEBAR_W / 100;

    SDL_Rect upperBg = {0, 0, (Uint16) (percentLife * divPerPercent), 7};
    SDL_Rect middleBg = {0, 7, (Uint16) (percentLife * divPerPercent), 20};
    SDL_Rect lowerBg = {0, 27, (Uint16) (percentLife * divPerPercent), 7};

    Uint32 upperColor;
    Uint32 middleColor;
    Uint32 lowerColor;

    if (percentLife > 66) {
        upperColor = SDL_MapRGB(result->format, 40, 225, 40);
        middleColor = SDL_MapRGB(result->format, 1, 180, 1);
        lowerColor = SDL_MapRGB(result->format, 1, 151, 1);
    } else if (percentLife > 33) {
        upperColor = SDL_MapRGB(result->format, 250, 186, 40);
        middleColor = SDL_MapRGB(result->format, 247, 160, 24);
        lowerColor = SDL_MapRGB(result->format, 217, 163, 22);
    } else {
        upperColor = SDL_MapRGB(result->format, 242, 112, 95);
        middleColor = SDL_MapRGB(result->format, 237, 49, 58);
        lowerColor = SDL_MapRGB(result->format, 164, 57, 53);
    }

    SDL_FillRect(result, &upperBg, upperColor);
    SDL_FillRect(result, &middleBg, middleColor);
    SDL_FillRect(result, &lowerBg, lowerColor);

    return result;
}

static void renderKeys(SDL_Surface* window, Engine* engine, Data* data) {
    SDL_Surface* keys = get_ImageCollector(engine->imageCollector, "dungeon/uiKeys")->surface;
    int amount = 0;

    if (true) { // TODO: Key1 condition
        SDL_Rect offset;
        offset.x = 329;
        offset.y = 29;

        SDL_Rect sheet;
        sheet.x = 0;
        sheet.y = 0;
        sheet.w = 46;
        sheet.h = 23;

        SDL_BlitSurface(keys, &sheet, window, &offset);

        amount += 1;
    }

    if (true) { // TODO: Key2 condition
        SDL_Rect offset;
        offset.x = 329 + 14 * amount +  46 * amount;
        offset.y = 29;

        SDL_Rect sheet;
        sheet.x = 46;
        sheet.y = 0;
        sheet.w = 46;
        sheet.h = 23;

        SDL_BlitSurface(keys, &sheet, window, &offset);

        amount += 1;
    }

    if (true) { // TODO: Key3 condition
        SDL_Rect offset;
        offset.x = 329 + 14 * amount +  46 * amount;
        offset.y = 29;

        SDL_Rect sheet;
        sheet.x = 92;
        sheet.y = 0;
        sheet.w = 46;
        sheet.h = 23;

        SDL_BlitSurface(keys, &sheet, window, &offset);

        amount += 1;
    }
}

static void renderMap(SDL_Surface* window, Engine* engine, Data* data) {
    // x: 1116 y: 36px w: 150px h: 150px
    SDL_Surface* start = get_ImageCollector(engine->imageCollector, "dungeon/mapStart")->surface;
    SDL_Surface* boss = get_ImageCollector(engine->imageCollector, "dungeon/mapBoss")->surface;
    SDL_Surface* goal = get_ImageCollector(engine->imageCollector, "dungeon/mapGoal")->surface;
    SDL_Surface* room = get_ImageCollector(engine->imageCollector, "dungeon/mapRoom")->surface;
    SDL_Surface* roomVisited = get_ImageCollector(engine->imageCollector, "dungeon/mapRoomVisited")->surface;
    SDL_Surface* roomCurrent = get_ImageCollector(engine->imageCollector, "dungeon/mapRoomCurrent")->surface;

    int x = data->dungeonScene->currentRoom->coord->x;
    int y = data->dungeonScene->currentRoom->coord->y;

    RoomList* temp = (*getRooms_KeyLevelRoomMapping(getRooms_Dungeon(data->dungeonScene->dungeon), 0));

    while (temp != NULL) {
        int offsetX = (temp->data->coord->x - x);
        int offsetY = (temp->data->coord->y - y);

        if (offsetX < 3 && offsetX > -3 && offsetY < 3 && offsetY > -3) {
            SDL_Rect pos;
            pos.x = (Sint16) (1116 + 25 * 2 + offsetX * 25);
            pos.y = (Sint16) (36 + 25 * 2 + offsetY * 25);

            if (temp->data->visited == true) {
                if (isStart_Room(temp->data)) {
                    SDL_BlitSurface(start, NULL, window, &pos);
                } else if (isBoss_Room(temp->data)) {
                    SDL_BlitSurface(boss, NULL, window, &pos);
                } else if (isGoal_Room(temp->data)) {
                    SDL_BlitSurface(goal, NULL, window, &pos);
                } else {
                    SDL_BlitSurface(roomVisited, NULL, window, &pos);
                }

                if (offsetX == 0 && offsetY == 0) {
                    SDL_BlitSurface(roomCurrent, NULL, window, &pos);
                }

                SDL_Rect posRoom;
                posRoom.x = pos.x;
                posRoom.y = pos.y;

                for (int i = 0; i < (int) temp->data->childrenLength; i += 1) {
                    offsetX = (temp->data->children[i]->coord->x - x);
                    offsetY = (temp->data->children[i]->coord->y - y);

                    int direction = getDirectionTo_Coord(temp->data->children[i]->coord, temp->data->coord)->code;
                    renderMapDoor(window, engine, data, posRoom, direction);

                    if (offsetX < 3 && offsetX > -3 && offsetY < 3 && offsetY > -3) {
                        pos.x = (Sint16) (1116 + 25 * 2 + offsetX * 25);
                        pos.y = (Sint16) (36 + 25 * 2 + offsetY * 25);

                        if (isStart_Room(temp->data->children[i])) {
                            SDL_BlitSurface(start, NULL, window, &pos);
                        } else if (isBoss_Room(temp->data->children[i])) {
                            SDL_BlitSurface(boss, NULL, window, &pos);
                        } else if (isGoal_Room(temp->data->children[i])) {
                            SDL_BlitSurface(goal, NULL, window, &pos);
                        } else if (temp->data->children[i]->visited == false) {
                            SDL_BlitSurface(room, NULL, window, &pos);
                        }
                    }
                }

                if (getParent_Room(temp->data) != NULL) {
                    int direction = getDirectionTo_Coord(temp->data->parent->coord, temp->data->coord)->code;
                    renderMapDoor(window, engine, data, posRoom, direction);
                }
            }
        }

        temp = temp->next;
    }
}

static void renderMapDoor(SDL_Surface* window, Engine* engine, Data* data, SDL_Rect origin, int direction) {
    SDL_Surface* doors = get_ImageCollector(engine->imageCollector, "dungeon/mapDoors")->surface;

    switch(direction) {
        case NORTH: {
            SDL_Rect door_Pos;
            SDL_Rect door_Offset;

            door_Offset.x = 2;
            door_Offset.y = 0;
            door_Offset.w = 6;
            door_Offset.h = 2;

            door_Pos.x = (Sint16) ((origin.x + 25 / 2) - (6 / 2));
            door_Pos.y = (Sint16) (origin.y);

            SDL_BlitSurface(doors, &door_Offset, window, &door_Pos);

            break;
        }

        case EAST: {
            SDL_Rect door_Pos;
            SDL_Rect door_Offset;

            door_Offset.x = 0;
            door_Offset.y = 0;
            door_Offset.w = 2;
            door_Offset.h = 6;

            door_Pos.x = (Sint16) ((origin.x + 25 - 2));
            door_Pos.y = (Sint16) ((origin.y + 25 / 2) - (6 / 2));

            SDL_BlitSurface(doors, &door_Offset, window, &door_Pos);

            break;
        }

        case SOUTH: {
            SDL_Rect door_Pos;
            SDL_Rect door_Offset;

            door_Offset.x = 2;
            door_Offset.y = 0;
            door_Offset.w = 6;
            door_Offset.h = 2;

            door_Pos.x = (Sint16) ((origin.x + 25 / 2) - (6 / 2));
            door_Pos.y = (Sint16) (origin.y + 25 - 2);

            SDL_BlitSurface(doors, &door_Offset, window, &door_Pos);

            break;
        }

        case WEST: {
            SDL_Rect door_Pos;
            SDL_Rect door_Offset;

            door_Offset.x = 0;
            door_Offset.y = 0;
            door_Offset.w = 2;
            door_Offset.h = 6;

            door_Pos.x = (Sint16) ((origin.x));
            door_Pos.y = (Sint16) ((origin.y + 25 / 2) - (6 / 2));

            SDL_BlitSurface(doors, &door_Offset, window, &door_Pos);

            break;
        }

        default: {
            break;
        }
    }
}


extern void renderScene_Scene_dungeon(SDL_Surface* window, Engine* engine, Data* data) {
    renderBackground(window, engine, data);

    renderUI(window, engine, data);
    renderMap(window, engine, data);
}