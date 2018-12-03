#include "render.h"
#include "../../engine/game/dungeon/dungeon.h"
#include "../../engine/game/dungeon/roomlist.h"

static void renderUI(SDL_Surface* window, Engine* engine, Data* data);
static SDL_Surface* renderLifebar(Engine* engine, Data* data);
static void renderKeys(SDL_Surface* window, Engine* engine, Data* data);
static void renderMap(SDL_Surface* window, Engine* engine, Data* data);

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
    uiPlayer_Pos.x = 21;
    uiPlayer_Pos.y = 16;
    SDL_Rect uiLifebarBg_Pos;
    uiLifebarBg_Pos.x = 92;
    uiLifebarBg_Pos.y = 20;
    SDL_Rect uiLifebar_Pos;
    uiLifebar_Pos.x = 95;
    uiLifebar_Pos.y = 23;
    SDL_Rect mapBG_Pos;
    mapBG_Pos.x = 1096;
    mapBG_Pos.y = 16;

    SDL_BlitSurface(uiPlayer, NULL, window, &uiPlayer_Pos);
    SDL_BlitSurface(uiLifebarBg, NULL, window, &uiLifebarBg_Pos);
    SDL_BlitSurface(uiLifebar, NULL, window, &uiLifebar_Pos);
    SDL_BlitSurface(mapBG, NULL, window, &mapBG_Pos);

    renderKeys(window, engine, data);

    SDL_FreeSurface(uiLifebar);
}

static SDL_Surface* renderLifebar(Engine* engine, Data* data) {
    SDL_Surface* result = SDL_CreateRGBSurface(SDL_HWSURFACE, 217, 34, 32, 0, 0, 0, 0);

    float percentLife = (data->Isaac->stats->current->health / data->Isaac->stats->basic->health) * 100;
    float divPerPercent = (float) 217 / 100;

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

                for (int i = 0; i < (int) temp->data->childrenLength; i += 1) {
                    offsetX = (temp->data->children[i]->coord->x - x);
                    offsetY = (temp->data->children[i]->coord->y - y);

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
            }


            // TODO: Improve here
        }

        temp = temp->next;
    }
}


extern void renderScene_Scene_dungeon(SDL_Surface* window, Engine* engine, Data* data) {
    renderUI(window, engine, data);
    renderMap(window, engine, data);
}