#include <math.h>
#include "render.h"
#include "../../engine/game/dungeon/dungeon.h"
#include "../../engine/game/dungeon/roomlist.h"
#include "constants.h"

static void renderBackground(SDL_Surface* window, Engine* engine, Data* data);
static void renderDoors(SDL_Surface* window, Engine* engine, Data* data);
static void renderDoor(SDL_Surface* window, Engine* engine, Data* data, int direction, int symbol);

static void renderUI(SDL_Surface* window, Engine* engine, Data* data);
static SDL_Surface* renderLifebar(Engine* engine, Data* data);
static void renderKeys(SDL_Surface* window, Engine* engine, Data* data);
static void renderMap(SDL_Surface* window, Engine* engine, Data* data);
static void renderMapDoor(SDL_Surface* window, Engine* engine, Data* data, SDL_Rect origin, int direction);

static void renderDamageAmountIndicator(Engine* engine, Data* data, SDL_Surface* window, SDL_Rect offset, float amount);

static void renderEntities(EntityList* entity,SDL_Surface* window, Engine* engine,Data* data);

static void renderCloudEntities(EntityList* entity,SDL_Surface* window, Engine* engine,Data* data);

static void displayDeathScreen(SDL_Surface* window, Engine* engine, Data* data);

static void renderCloudEntities(EntityList* entity,SDL_Surface* window, Engine* engine,Data* data)
{
    EntityList* current=entity;
    SDL_Surface* DeadGuy=NULL;
    SDL_Rect cloudpos;
    DeadGuy= get_ImageCollector(engine->imageCollector, "dungeon/smoke")->surface;// remove

    while(current)
    {
        SDL_Rect cloudpos,cloudsprite;
        cloudpos.x= (current->data->movement->hitBox->x+(current->data->movement->hitBox->w/2))-96;
        cloudpos.y= (current->data->movement->hitBox->y+(current->data->movement->hitBox->h/2))-96;


        int step=(current->data->movement->animationStep/50);
        if(step>3 && step<16){step=3;}
        if(step>15){step=19-step;}
        cloudsprite.x=step * 192;
        cloudsprite.y=0;
        cloudsprite.h=192;
        cloudsprite.w=192;
        SDL_BlitSurface(DeadGuy, &cloudsprite, window, &cloudpos);

        DamageIndicatorQueueNode* damageIndicator = deQueue_DamageIndicator(data->dyingEntities->data->damageIndicatorQueue);
        while (damageIndicator != NULL) {
            renderDamageAmountIndicator(engine, data,window, *damageIndicator->data->position, damageIndicator->data->amount);
            damageIndicator = damageIndicator->next;
        }


        current=current->next;
    }

}


static void renderEntities(EntityList* entity, SDL_Surface* window, Engine* engine,Data* data)
{
    EntityList* current=entity;
    SDL_Surface* BadGuy=NULL;
    SDL_Rect monsterpos;



    while(current)
    {
        switch(current->data->type)
        {
            case MOTH:
                BadGuy = get_ImageCollector(engine->imageCollector, "dungeon/moth")->surface;
                break;
            case WORM:
                BadGuy = get_ImageCollector(engine->imageCollector, "dungeon/worm")->surface;
                break;
            case PROJECTILE:
                switch(current->data->movement->direction)
                {
                    case 1:
                        BadGuy = get_ImageCollector(engine->imageCollector, "dungeon/wormshot")->surface;
                        break;
                    default:
                        break;
                }
                BadGuy = get_ImageCollector(engine->imageCollector, "dungeon/wormshot")->surface;
            default:
                printf("Something is wrong here\n");
                break;
        }
        monsterpos.x = (Sint16) current->data->movement->position->x; // remove
        monsterpos.y = (Sint16) current->data->movement->position->y;
        SDL_BlitSurface(BadGuy, current->data->movement->spriteBox, window, &monsterpos);

        DamageIndicatorQueueNode* damageIndicator = deQueue_DamageIndicator(current->data->damageIndicatorQueue);
        while (damageIndicator != NULL) {
            renderDamageAmountIndicator(engine, data, window, *damageIndicator->data->position, damageIndicator->data->amount);
            damageIndicator = damageIndicator->next;
        }
        current=current->next;
    }
}

static void renderDamageAmountIndicator(Engine* engine, Data* data, SDL_Surface* window, SDL_Rect offset, float amount) {
    SDL_Surface* damageSpritesheet = get_ImageCollector(engine->imageCollector, "dungeon/damageAmount")->surface;

    int array[10];

    for (int i = 0; i < 10; i += 1) {
        array[i] = 27;
    }

    double left;
    double right = modf(amount, &left);

    int integer = (int) left;
    int decimal = (int) (right * 10);

    int i = 7;

    while (integer != 0) {
        array[i] = integer % 10;
        i -= 1;

        if (i == -1) {
            break;
        }

        integer /= 10;
    }

    if (decimal > 0) {
        array[8] = 25;
        array[9] = decimal;
    } else {
        array[8] = 30;
        array[9] = 30;
    }

    for (i = 0; i < 10; i += 1) {
        switch(array[i]) {
            case 27: {
                break;
            }

            case 30: {
                break;
            }

            case 25: {
                SDL_Rect spriteOffset;
                spriteOffset.w = 8;
                spriteOffset.h = 16;
                spriteOffset.x = 162;
                spriteOffset.y = 0;

                SDL_BlitSurface(damageSpritesheet, &spriteOffset, window, &offset);

                offset.x += spriteOffset.w;

                break;
            }

            case 1: {
                SDL_Rect spriteOffset;
                spriteOffset.w = 9;
                spriteOffset.h = 16;
                spriteOffset.x = 0;
                spriteOffset.y = 0;

                SDL_BlitSurface(damageSpritesheet, &spriteOffset, window, &offset);

                offset.x += spriteOffset.w;

                break;
            }

            default: {
                SDL_Rect spriteOffset;
                spriteOffset.w = 17;
                spriteOffset.h = 16;
                spriteOffset.x = (Sint16) (9 + 17 * (array[i] - 2));
                spriteOffset.y = 0;

                SDL_BlitSurface(damageSpritesheet, &spriteOffset, window, &offset);

                offset.x += spriteOffset.w;
            }
        }
    }
}

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
    SDL_Surface* FightSprite=NULL;
    SDL_Surface* BadGuy=NULL; // remove
    SDL_Surface* DeadGuy=NULL;

    SDL_Rect playerPos;
    SDL_Rect monsterpos;

    PlayerSprite = get_ImageCollector(engine->imageCollector, "dungeon/player")->surface;
    FightSprite = get_ImageCollector(engine->imageCollector, "dungeon/scythe")->surface;

    playerPos.x=data->Isaac->movement->position->x;
    playerPos.y=data->Isaac->movement->position->y;


    renderCloudEntities(data->dyingEntities,window,engine,data);
    
    renderEntities(data->entities,window,engine,data);





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
        if (data->dungeonScene->askCombat != -1) {
            playerPos.y -= 32;
            playerPos.x -= 64;

            SDL_BlitSurface(FightSprite, data->Isaac->combat->spriteBox, window, &playerPos);
        } else {
            SDL_BlitSurface(PlayerSprite, data->Isaac->movement->spriteBox, window, &playerPos);
        }
    }




    /* see door hitboxes for debugging
    SDL_Surface * Hibox= get_ImageCollector(engine->imageCollector, "dungeon/hibox")->surface;
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
        int symbol = getKeyLevel_Condition(getPrecondition_Room(data->dungeonScene->currentRoom->children[i])) - 1;

        renderDoor(window, engine, data, direction, symbol);
    }

    if (getParent_Room(data->dungeonScene->currentRoom) != NULL) {
        int direction = getDirectionTo_Coord(data->dungeonScene->currentRoom->parent->coord, data->dungeonScene->currentRoom->coord)->code;
        renderDoor(window, engine, data, direction, 0);
    }
}

static void renderDoor(SDL_Surface* window, Engine* engine, Data* data, int direction, int symbol) {
    SDL_Surface* doors = get_ImageCollector(engine->imageCollector, "dungeon/tomatoDoors")->surface;

    int offset;

    if (direction == NORTH || direction == SOUTH) {
        if (data->dungeonScene->currentRoom->cleaned == false || symbol > data->dungeonScene->keyValue) {
            switch(symbol) {
                case 0: {
                    offset = 0;

                    break;
                }

                case 1: {
                    offset = 256;

                    break;
                }

                case 2: {
                    offset = 128;

                    break;
                }

                case 3: {
                    offset = 192;

                    break;
                }

                default: {
                    offset = 0;

                    break;
                }
            }
        } else {
            offset = 64;
        }
    } else if (direction == EAST || direction == WEST) {
        if (data->dungeonScene->currentRoom->cleaned == false || symbol > data->dungeonScene->keyValue) {
            switch(symbol) {
                case 0: {
                    offset = 6;

                    break;
                }

                case 1: {
                    offset = 198;

                    break;
                }

                case 2: {
                    offset = 134;

                    break;
                }

                case 3: {
                    offset = 262;

                    break;
                }

                default: {
                    offset = 6;

                    break;
                }
            }
        } else if (data->dungeonScene->keyValue >= symbol) {
            offset = 70;
        }
    }

    switch (direction) {
        case NORTH: {
            SDL_Rect door_Pos;
            SDL_Rect door_Offset;

            door_Offset.x = 64;
            door_Offset.y = (Sint16) offset;
            door_Offset.w = 110;
            door_Offset.h = 64;

            door_Pos.x = (Sint16) ((window->w / 2) -  door_Offset.w / 2);
            door_Pos.y = 8;

            SDL_BlitSurface(doors, &door_Offset, window, &door_Pos);

            break;
        }

        case EAST: {
            SDL_Rect door_Pos;
            SDL_Rect door_Offset;

            door_Offset.x = 0;
            door_Offset.y = (Sint16) offset;
            door_Offset.w = 64;
            door_Offset.h = 52;

            door_Pos.x = (Sint16) ((window->w) -  door_Offset.w);
            door_Pos.y = (Sint16) ((window->h / 2) - door_Offset.h / 2);

            SDL_BlitSurface(doors, &door_Offset, window, &door_Pos);

            break;
        }

        case SOUTH: {
            SDL_Rect door_Pos;
            SDL_Rect door_Offset;

            door_Offset.x = 238;
            door_Offset.y = (Sint16) offset;
            door_Offset.w = 110;
            door_Offset.h = 64;

            door_Pos.x = (Sint16) ((window->w / 2) -  door_Offset.w / 2);
            door_Pos.y = (Sint16) ((window->h - 8) - door_Offset.h);

            SDL_BlitSurface(doors, &door_Offset, window, &door_Pos);

            break;
        }

        case WEST: {
            SDL_Rect door_Pos;
            SDL_Rect door_Offset;

            door_Offset.x = 174;
            door_Offset.y = (Sint16) offset;
            door_Offset.w = 64;
            door_Offset.h = 52;

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

    if (data->dungeonScene->keyValue > 0) {
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

    if (data->dungeonScene->keyValue > 1) {
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

    if (data->dungeonScene->keyValue > 2) {
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

    KeyLevelRoomMapping* level = getRooms_Dungeon(data->dungeonScene->dungeon);
    RoomList* rooms = (*getRooms_KeyLevelRoomMapping(level, 0));

    RoomList* temp = rooms;

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

    clean_KeyLevelRoomMapping(&(level));
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

static void displayDeathScreen(SDL_Surface* window, Engine* engine, Data* data) {
    if(!isPlayerAlive(data->Isaac)) {
        char line[80];
        SDL_Color colorUsed = {255, 255, 255, 0};
        TTF_Font* font1 = get_FontCollector(engine->fontCollector, "menu/50")->font;

        SDL_Surface* dialogBox = get_ImageCollector(engine->imageCollector, "dungeon/dialog")->surface;
        SDL_Surface* dialogInfo;
        SDL_Rect dialogBoxPos;
        SDL_Rect dialogPos;

        dialogBoxPos.x = 145;
        dialogBoxPos.y = 278;
        SDL_BlitSurface(dialogBox, NULL, window, &dialogBoxPos);


        for(int i = 0; i < 2; i++) {
            switch(i) {
                case 0: {
                    strcpy(line, "You died... You'll do better next time.");
                    dialogPos.x = (Sint16) (145 + ((1010 / 2) - (getWidth_FontCollector(font1, line) / 2)));
                    dialogPos.y = (Sint16) 290;
                    break;
                }
                case 1: {
                    strcpy(line, "Press ESC to restart.");
                    dialogPos.x = (Sint16) (145 + ((1010 / 2) - (getWidth_FontCollector(font1, line) / 2)));
                    dialogPos.y = (Sint16) 360;
                    break;
                }
            }
            dialogInfo = TTF_RenderText_Solid(font1, line, colorUsed);
            SDL_BlitSurface(dialogInfo, NULL, window, &dialogPos);
        }
    }
}


extern void renderScene_Scene_dungeon(SDL_Surface* window, Engine* engine, Data* data) {
    renderBackground(window, engine, data);

    renderUI(window, engine, data);
    renderMap(window, engine, data);

    displayDeathScreen(window, engine, data);

    SDL_BlitSurface(window, NULL, data->dungeonScene->pauseBg, NULL);
}