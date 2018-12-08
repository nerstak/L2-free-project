#include <math.h>

#include "render.h"

#include "../../window.h"

static void renderDamageAmountIndicator(Engine* engine, Data* data, SDL_Surface* window, SDL_Rect offset, float amount);

static SDL_Surface* getLobby(Engine* engine, Data* data);

static void renderDamageAmountIndicator(Engine* engine, Data* data, SDL_Surface* window, SDL_Rect offset, float amount) {
    SDL_Surface* damageSpritesheet = get_ImageCollector(engine->imageCollector, "lobby/damageAmount")->surface;

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

static SDL_Surface* getLobby(Engine* engine, Data* data) {
    SDL_Surface* lobbySurface = NULL;
    lobbySurface = SDL_CreateRGBSurface(SDL_HWSURFACE, 1280, 720, 32, 0, 0, 0, 0);


    SDL_Surface* bg = NULL;

    SDL_Surface* PlayerSprite=NULL;

    SDL_Surface* FightSprite=NULL;

    SDL_Surface* BadGuy=NULL; // remove

    SDL_Surface* Hibox=NULL;

    SDL_Rect bgPos;
    SDL_Rect playerPos;
    SDL_Rect monsterpos;

    bg = get_ImageCollector(engine->imageCollector, "lobby/bg")->surface;
    FightSprite = get_ImageCollector(engine->imageCollector, "lobby/scythe")->surface;

    Hibox= get_ImageCollector(engine->imageCollector, "lobby/hibox")->surface;
    BadGuy = get_ImageCollector(engine->imageCollector, "lobby/moth")->surface;// remove

    bgPos.x = 0;
    bgPos.y = 0;
    playerPos.x = (Sint16) data->Isaac->movement->position->x;
    playerPos.y = (Sint16) data->Isaac->movement->position->y;

    if(data->entities != NULL){
        monsterpos.x = (Sint16) data->entities->data->movement->position->x; // remove
        monsterpos.y = (Sint16) data->entities->data->movement->position->y;
    }

    if(data->lobby->actionProcess == NONE){ // TODO: Duplicate sprite here
        bg = get_ImageCollector(engine->imageCollector, "lobby/bg")->surface;
        PlayerSprite = get_ImageCollector(engine->imageCollector, "lobby/player")->surface;

    }
    else{
        bg = get_ImageCollector(engine->imageCollector, "lobby/bg_flou")->surface;
        PlayerSprite = get_ImageCollector(engine->imageCollector, "lobby/player_flou")->surface;
    }

    SDL_BlitSurface(bg, NULL, lobbySurface, &bgPos);

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
        if (data->lobby->askCombat != -1) {
            playerPos.y -= 32;
            playerPos.x -= 64;

            SDL_BlitSurface(FightSprite, data->Isaac->combat->spriteBox, lobbySurface, &playerPos);
        } else {
            SDL_BlitSurface(PlayerSprite, data->Isaac->movement->spriteBox, lobbySurface, &playerPos);
        }
    }

    if (data->entities != NULL) {
        SDL_BlitSurface(BadGuy, data->entities->data->movement->spriteBox, lobbySurface, &monsterpos);

        DamageIndicatorQueueNode* damageIndicator = deQueue_DamageIndicator(data->entities->data->damageIndicatorQueue);
        while (damageIndicator != NULL) {
            renderDamageAmountIndicator(engine, data, lobbySurface, *damageIndicator->data->position, damageIndicator->data->amount);
            damageIndicator = damageIndicator->next;
        }
    }

    if(data->lobby->actionProcess == SLEEP){
        SDL_Color black = {0, 0, 0, 0};

        TTF_Font* font1 = NULL;
        font1 = get_FontCollector(engine->fontCollector, "menu/90")->font;

        TTF_Font* font2 = NULL;
        font2 = get_FontCollector(engine->fontCollector, "menu/75")->font;

        SDL_Surface* interface = NULL;
        SDL_Surface* menu1x1;
        SDL_Surface* menu1x2;
        SDL_Surface* menu1x3;

        if(data->lobby->cursor == 0){
            interface = get_ImageCollector(engine->imageCollector, "lobby/menu11")->surface;
        }else if (data->lobby->cursor == 1){
            interface = get_ImageCollector(engine->imageCollector, "lobby/menu12")->surface;
        }
        menu1x1 = TTF_RenderText_Solid(font1, "Save Game?", black);
        menu1x2 = TTF_RenderText_Solid(font2, "YES", black);
        menu1x3 = TTF_RenderText_Solid(font2, "NO", black);

        SDL_Rect posMenu1x1;
        SDL_Rect posMenu1x2;
        SDL_Rect posMenu1x3;
        SDL_Rect posMenu1xInterface;

        posMenu1xInterface.x = 0;
        posMenu1xInterface.y = 0;

        posMenu1x1.x = (Sint16) (posMenu1xInterface.x + 450);
        posMenu1x1.y = (Sint16) (posMenu1xInterface.y + 345);

        posMenu1x2.x = (Sint16) (posMenu1x1.x - 220);
        posMenu1x2.y = (Sint16) (posMenu1x1.y - 10);

        posMenu1x3.x = (Sint16) (posMenu1x1.x + 550);
        posMenu1x3.y = (Sint16) (posMenu1x1.y - 10);

        SDL_BlitSurface(interface, NULL, lobbySurface, &posMenu1xInterface);
        SDL_BlitSurface(menu1x1, NULL, lobbySurface, &posMenu1x1);
        SDL_BlitSurface(menu1x2, NULL, lobbySurface, &posMenu1x2);
        SDL_BlitSurface(menu1x3, NULL, lobbySurface, &posMenu1x3);
    }

    if(data->lobby->actionProcess == PLANT){
        SDL_Surface* menuPlant = NULL;
        SDL_Surface* menuPlantSelect = NULL;

        SDL_Rect posMenuPlant;
        SDL_Rect posMenuPlantSelect;

        posMenuPlant.x = 0 ;
        posMenuPlant.y = 0 ;

        posMenuPlantSelect.x = (Sint16) (188 * (data->lobby->cursor));
        posMenuPlantSelect.y = 0 ;

        menuPlantSelect = get_ImageCollector(engine->imageCollector, "lobby/menu22")->surface;
        menuPlant = get_ImageCollector(engine->imageCollector, "lobby/menu21")->surface;

        SDL_BlitSurface(menuPlant, NULL, lobbySurface, &posMenuPlant);
        SDL_BlitSurface(menuPlantSelect, NULL, lobbySurface, &posMenuPlantSelect);
    }

    if(data->lobby->actionProcess == GOTO_DUNGEON ){
        SDL_Color black = {0, 0, 0, 0};

        TTF_Font* font1 = NULL;
        font1 = get_FontCollector(engine->fontCollector, "menu/65")->font;

        TTF_Font* font2 = NULL;
        font2 = get_FontCollector(engine->fontCollector, "menu/75")->font;

        SDL_Surface* interface = NULL;
        SDL_Surface* menu1x1;
        SDL_Surface* menu1x2;
        SDL_Surface* menu1x3;

        if(data->lobby->cursor == 0){
            interface = get_ImageCollector(engine->imageCollector, "lobby/menu11")->surface;
        }else if (data->lobby->cursor == 1){
            interface = get_ImageCollector(engine->imageCollector, "lobby/menu12")->surface;
        }

        menu1x1 = TTF_RenderText_Solid(font1, "Dare you enter?", black);
        menu1x2 = TTF_RenderText_Solid(font2, "YES", black);
        menu1x3 = TTF_RenderText_Solid(font2, "NO", black);

        SDL_Rect posMenu1x1;
        SDL_Rect posMenu1x2;
        SDL_Rect posMenu1x3;
        SDL_Rect posMenu1xInterface;

        posMenu1xInterface.x = 0;
        posMenu1xInterface.y = 0;

        posMenu1x1.x =  450;
        posMenu1x1.y =  345;

        posMenu1x2.x = posMenu1x1.x-220;
        posMenu1x2.y = posMenu1x1.y-10;

        posMenu1x3.x = posMenu1x1.x+550;
        posMenu1x3.y = posMenu1x1.y-10;

        SDL_BlitSurface(interface, NULL, lobbySurface, &posMenu1xInterface);
        SDL_BlitSurface(menu1x1, NULL, lobbySurface, &posMenu1x1);
        SDL_BlitSurface(menu1x2, NULL, lobbySurface, &posMenu1x2);
        SDL_BlitSurface(menu1x3, NULL, lobbySurface, &posMenu1x3);
    }

    if(data->lobby->actionProcess == WAIT || data->lobby->actionProcess == NOT_ENOUGH ){
        SDL_Surface* wait = NULL;
        SDL_Surface* menu1x1;

        SDL_Rect posMenu1xInterface;
        SDL_Rect posMenu1x1;

        SDL_Color black = {0, 0, 0, 0};

        TTF_Font* font1 = NULL;
        font1 = get_FontCollector(engine->fontCollector, "menu/90")->font;

        wait = get_ImageCollector(engine->imageCollector, "lobby/wait")->surface;

        if(data->lobby->actionProcess == WAIT){
            menu1x1 = TTF_RenderText_Solid(font1, "Wait Dude !", black);
        }else if(data->lobby->actionProcess == NOT_ENOUGH){
            menu1x1 = TTF_RenderText_Solid(font1, "No Seed !", black);
        }

        posMenu1xInterface.x = 0;
        posMenu1xInterface.y = 0;

        posMenu1x1.x = posMenu1xInterface.x + 470;

        if(data->lobby->actionProcess == WAIT){
            posMenu1x1.x -= 50;
        }

        posMenu1x1.y = posMenu1xInterface.y + 320;

        SDL_BlitSurface(wait, NULL, lobbySurface, &posMenu1xInterface);
        SDL_BlitSurface(menu1x1, NULL, lobbySurface, &posMenu1x1);
    }



    //SDL_BlitSurface(Hibox, &hisprite, lobbySurface, &hibpos);// remove
    return lobbySurface;
}



extern void renderScene_Scene_lobby(SDL_Surface* window, Engine* engine, Data* data) {
    SDL_Surface* lobbySurface = NULL;
    lobbySurface = getLobby(engine, data);

    SDL_Rect lobbySurfacePos;
    lobbySurfacePos.x = 0;
    lobbySurfacePos.y = 0;

    applySurface_Window(lobbySurface, window, lobbySurfacePos);

    SDL_FreeSurface(lobbySurface);
}

