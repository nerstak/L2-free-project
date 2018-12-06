#include "render.h"
#include "../../window.h"

static SDL_Surface* getLobby(ImageCollector* myImageCollector, FontCollector* myFontCollector, Data* data);

static SDL_Surface* getLobby(ImageCollector* myImageCollector, FontCollector* myFontCollector, Data* data) {
    SDL_Surface* lobbySurface = NULL;
    lobbySurface = SDL_CreateRGBSurface(SDL_HWSURFACE, 1280, 720, 32, 0, 0, 0, 0);

    //Declaration of surface

    SDL_Surface* bg = NULL;
    SDL_Surface* PlayerSprite=NULL;
    SDL_Surface* dialogBox = NULL;
    SDL_Surface* dialog = NULL;

    char line[150];

    SDL_Rect bgPos;
    SDL_Rect playerPos;
    SDL_Rect dialogBoxPos;
    SDL_Rect dialogPos;

    bgPos.x = 0;
    bgPos.y = 0;
    playerPos.x = data->Isaac->movement->pos->x;
    playerPos.y = data->Isaac->movement->pos->y;




    // Stuff
    if(data->lobby->actionProcess == NONE){
        bg = get_ImageCollector(myImageCollector, "lobby/bg")->surface;
        PlayerSprite = get_ImageCollector(myImageCollector, "lobby/player")->surface;

        SDL_BlitSurface(bg, NULL, lobbySurface, &bgPos);
        SDL_BlitSurface(PlayerSprite, data->Isaac->movement->SpriteBox, lobbySurface, &playerPos);
    }else{
        bg = get_ImageCollector(myImageCollector, "lobby/bg_flou")->surface;
        PlayerSprite = get_ImageCollector(myImageCollector, "lobby/player_flou")->surface;

        SDL_BlitSurface(bg, NULL, lobbySurface, &bgPos);
        SDL_BlitSurface(PlayerSprite, data->Isaac->movement->SpriteBox, lobbySurface, &playerPos);
    }


    if(data->lobby->actionProcess == SLEEP){
        SDL_Color black = {0, 0, 0, 0};

        TTF_Font* font1 = NULL;
        font1 = get_FontCollector(myFontCollector, "menu/90")->font;

        TTF_Font* font2 = NULL;
        font2 = get_FontCollector(myFontCollector, "menu/75")->font;

        SDL_Surface* interface = NULL;
        SDL_Surface* menu1x1;
        SDL_Surface* menu1x2;
        SDL_Surface* menu1x3;

        if(data->lobby->cursor == 0){
            interface = get_ImageCollector(myImageCollector, "lobby/menu11")->surface;
        }else if (data->lobby->cursor == 1){
            interface = get_ImageCollector(myImageCollector, "lobby/menu12")->surface;
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

        posMenu1x1.x = posMenu1xInterface.x + 450;
        posMenu1x1.y = posMenu1xInterface.y + 345;

        posMenu1x2.x = posMenu1x1.x-220;
        posMenu1x2.y = posMenu1x1.y-10;

        posMenu1x3.x = posMenu1x1.x+550;
        posMenu1x3.y = posMenu1x1.y-10;

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

        menuPlantSelect = get_ImageCollector(myImageCollector, "lobby/menu22")->surface;
        menuPlant = get_ImageCollector(myImageCollector, "lobby/menu21")->surface;

        SDL_BlitSurface(menuPlant, NULL, lobbySurface, &posMenuPlant);
        SDL_BlitSurface(menuPlantSelect, NULL, lobbySurface, &posMenuPlantSelect);
    }

    if(data->lobby->actionProcess == GOTO_DUNGEON ){
        SDL_Color black = {0, 0, 0, 0};

        TTF_Font* font1 = NULL;
        font1 = get_FontCollector(myFontCollector, "menu/65")->font;

        TTF_Font* font2 = NULL;
        font2 = get_FontCollector(myFontCollector, "menu/75")->font;

        SDL_Surface* interface = NULL;
        SDL_Surface* menu1x1;
        SDL_Surface* menu1x2;
        SDL_Surface* menu1x3;

        if(data->lobby->cursor == 0){
            interface = get_ImageCollector(myImageCollector, "lobby/menu11")->surface;
        }else if (data->lobby->cursor == 1){
            interface = get_ImageCollector(myImageCollector, "lobby/menu12")->surface;
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
        font1 = get_FontCollector(myFontCollector, "menu/90")->font;

        wait = get_ImageCollector(myImageCollector, "lobby/wait")->surface;

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
    if(data->lobby->tutorial == 1) {
        SDL_Color black = {0, 0, 0, 0};
        TTF_Font* font1 = get_FontCollector(myFontCollector, "menu/25")->font;
        dialogBox = get_ImageCollector(myImageCollector, "lobby/dialog")->surface;

        dialogBoxPos.x = 135;
        dialogBoxPos.y = 541;
        SDL_BlitSurface(dialogBox, NULL, lobbySurface, &dialogBoxPos);

        dialogPos.x = 145;
        dialogPos.y = 545 - 35;

        for(int i = 0; i < 4; i++) {
            dialogPos.y += 35;
            switch(i) {
                case 0:
                    strcpy(line, "My old man died 2 days ago... He left me this crappy farm and seed with warning...");
                    break;
                case 1:
                    strcpy(line, "If I sold these, I couldn't even buy a Fornite skin's...");
                    break;
                case 2:
                    strcpy(line, "I should try to see in this cemetery if there's something valuable. Or is it a little garden?");
                    break;
                case 3:
                    strcpy(line, "Maybe should I become a farmer? If I plant my seed and wait long enough, I may become rich!");
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
    lobbySurface = getLobby(engine->imageCollector,engine->fontCollector,data);

    SDL_Rect lobbySurfacePos;
    lobbySurfacePos.x = 0;
    lobbySurfacePos.y = 0;

    applySurface_Window(lobbySurface, window, lobbySurfacePos);

    SDL_FreeSurface(lobbySurface);
}
