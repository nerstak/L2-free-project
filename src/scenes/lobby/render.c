#include <math.h>

#include "render.h"

#include "../../window.h"
#include "../../engine/config.h"
#include "../../engine/game/plants.h"

static SDL_Surface* getLobby(Engine* engine, Data* data);

static SDL_Surface* getLobby(Engine* engine, Data* data) {
    SDL_Surface* lobbySurface = NULL;
    lobbySurface = SDL_CreateRGBSurface(SDL_HWSURFACE, 1280, 720, 32, 0, 0, 0, 0);

    //Declaration of surface

    SDL_Surface* bg = NULL;
    SDL_Surface* PlayerSprite=NULL;
    SDL_Surface* dialogBox = NULL;
    SDL_Surface* dialog = NULL;

    SDL_Surface* FightSprite=NULL;

    SDL_Surface* Hibox=NULL;

    char line[150];

    SDL_Rect bgPos;
    SDL_Rect playerPos;
    SDL_Rect dialogBoxPos;
    SDL_Rect dialogPos;

    bg = get_ImageCollector(engine->imageCollector, "lobby/bg")->surface;
    FightSprite = get_ImageCollector(engine->imageCollector, "lobby/scythe")->surface;

    Hibox= get_ImageCollector(engine->imageCollector, "lobby/hibox")->surface;

    bgPos.x = 0;
    bgPos.y = 0;
    playerPos.x = (Sint16) data->Isaac->movement->position->x;
    playerPos.y = (Sint16) data->Isaac->movement->position->y;

    SDL_Color black = {0, 0, 0, 0};
    SDL_Color brown = {55, 25, 17, 0};

    if(data->lobby->actionProcess == NONE){
        bg = get_ImageCollector(engine->imageCollector, "lobby/bg")->surface;
        PlayerSprite = get_ImageCollector(engine->imageCollector, "lobby/player")->surface;

        SDL_BlitSurface(bg, NULL, lobbySurface, &bgPos);
        plantsBlit(lobbySurface, data, engine->imageCollector, 'c');
    }else{
        bg = get_ImageCollector(engine->imageCollector, "lobby/bg_flou")->surface;
        PlayerSprite = get_ImageCollector(engine->imageCollector, "lobby/player_flou")->surface;

        SDL_BlitSurface(bg, NULL, lobbySurface, &bgPos);
        plantsBlit(lobbySurface, data, engine->imageCollector, 'b');
    }

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


    if(data->lobby->actionProcess == SLEEP){
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
        menu1x1 = TTF_RenderText_Solid(font1, "Save Game?", brown);
        menu1x2 = TTF_RenderText_Solid(font2, "YES", brown);
        menu1x3 = TTF_RenderText_Solid(font2, "NO", brown);

        SDL_Rect posMenu1x1;
        SDL_Rect posMenu1x2;
        SDL_Rect posMenu1x3;
        SDL_Rect posMenu1xInterface;

        posMenu1xInterface.x = 0;
        posMenu1xInterface.y = 0;

        posMenu1x1.x = 425;
        posMenu1x1.y = 335;

        posMenu1x2.x = posMenu1x1.x - 221;
        posMenu1x2.y = posMenu1x1.y - 18;

        posMenu1x3.x = posMenu1x1.x + 550;
        posMenu1x3.y = posMenu1x1.y - 18;

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

        posMenuPlantSelect.x = (Sint16) (188 * (data->lobby->cursor) - 14);
        posMenuPlantSelect.y = 73;

        menuPlantSelect = get_ImageCollector(engine->imageCollector, "lobby/menu22")->surface;
        menuPlant = get_ImageCollector(engine->imageCollector, "lobby/menu21")->surface;

        SDL_BlitSurface(menuPlant, NULL, lobbySurface, &posMenuPlant);
        SDL_BlitSurface(menuPlantSelect, NULL, lobbySurface, &posMenuPlantSelect);
    }

    if(data->lobby->actionProcess == GOTO_DUNGEON ){

        TTF_Font* font1 = NULL;
        font1 = get_FontCollector(engine->fontCollector, "menu/65")->font;

        TTF_Font* font2 = NULL;
        font2 = get_FontCollector(engine->fontCollector, "menu/75")->font;

        SDL_Surface* interface = NULL;
        SDL_Surface* menu1x1;
        SDL_Surface* menu1x2;
        SDL_Surface* menu1x3;

        SDL_Rect posMenu1x1;
        SDL_Rect posMenu1x2;
        SDL_Rect posMenu1x3;
        SDL_Rect posMenu1xInterface;

        if(data->lobby->cursor == 0){
            interface = get_ImageCollector(engine->imageCollector, "lobby/menu11")->surface;
        }else if (data->lobby->cursor == 1){
            interface = get_ImageCollector(engine->imageCollector, "lobby/menu12")->surface;
        }

        menu1x1 = TTF_RenderText_Solid(font1, "Dare you enter?", brown); // Fucking relative layout @nerstak
        menu1x2 = TTF_RenderText_Solid(font2, "YES", brown);
        menu1x3 = TTF_RenderText_Solid(font2, "NO", brown);


        posMenu1xInterface.x = 0;
        posMenu1xInterface.y = 0;

        posMenu1x1.x = 425;
        posMenu1x1.y = 335;

        posMenu1x2.x = posMenu1x1.x - 221;
        posMenu1x2.y = posMenu1x1.y - 18;

        posMenu1x3.x = posMenu1x1.x + 550;
        posMenu1x3.y = posMenu1x1.y - 18;

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



    // Tutorial
    if(data->lobby->tutorial == 1 || data->lobby->tutorial == 3) {
        char name1[10], name2[10], name3[10], name4[10];
        SDL_Color black = {0, 0, 0, 0};
        TTF_Font* font1 = get_FontCollector(engine->fontCollector, "menu/25")->font;
        dialogBox = get_ImageCollector(engine->imageCollector, "lobby/dialog")->surface;

        dialogBoxPos.x = 135;
        dialogBoxPos.y = 541;
        SDL_BlitSurface(dialogBox, NULL, lobbySurface, &dialogBoxPos);

        dialogPos.x = 145;
        dialogPos.y = 545 - 35;

        for(int i = 0; i < 4; i++) {
            dialogPos.y += 35;
            switch(i) {
                case 0:
                    if(data->lobby->tutorial == 1) {
                        strcpy(line, "My old man died 2 days ago... He left me this crappy farm and seed with warning...");
                    } else {
                        strcpy(line, "Wow! I can move exactly like in Fornite!");
                    }
                    break;
                case 1:
                    if(data->lobby->tutorial == 1) {
                        strcpy(line, "If I sold these, I couldn't even buy a Fornite skin's...");
                    } else {
                        nameKeys(engine->keys->UP, name1);
                        nameKeys(engine->keys->DOWN, name2);
                        nameKeys(engine->keys->LEFT, name3);
                        nameKeys(engine->keys->RIGHT, name4);
                        sprintf(line, "I can use %s, %s, %s and %s to go somewhere", name1, name2, name3, name4);
                    }
                    break;
                case 2:
                    if(data->lobby->tutorial == 1) {
                        strcpy(line, "I should try to see in this cemetery if there's something valuable. Or is it a little garden?");
                    } else {
                        nameKeys(engine->keys->UP_ATTACK, name1);
                        nameKeys(engine->keys->DOWN_ATTACK, name2);
                        nameKeys(engine->keys->LEFT_ATTACK, name3);
                        nameKeys(engine->keys->RIGHT_ATTACK, name4);
                        sprintf(line, "But there's also %s, %s, %s and %s to use my tools", name1, name2, name3, name4);
                    }
                    break;
                case 3:
                    if(data->lobby->tutorial == 1) {
                        strcpy(line, "Maybe should I become a farmer? If I plant my seed and wait long enough, I may become rich!");
                    } else {
                        nameKeys(engine->keys->INVENTORY, name1);
                        nameKeys(engine->keys->DELETE, name2);
                        nameKeys(engine->keys->SELECT, name3);
                        sprintf(line, "I can open my bag with %s, and delete and item with %s. And to interact, I have %s.", name1, name2, name3);
                    }
                    break;
                default:
                    break;
            }
            dialog = TTF_RenderText_Solid(font1, line, black);
            SDL_BlitSurface(dialog, NULL, lobbySurface, &dialogPos);
        }
    }




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

