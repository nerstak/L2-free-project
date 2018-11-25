#include "render.h"
#include "../../window.h"

static SDL_Surface* getLobby(ImageCollector* myImageCollector, FontCollector* myFontCollector, Data* data);

static SDL_Surface* getLobby(ImageCollector* myImageCollector, FontCollector* myFontCollector, Data* data) {
    SDL_Surface* lobbySurface = NULL;
    lobbySurface = SDL_CreateRGBSurface(SDL_HWSURFACE, 1280, 720, 32, 0, 0, 0, 0);


    SDL_Surface* bg = NULL;

    SDL_Surface* PlayerSprite=NULL;

    SDL_Rect bgPos;
    SDL_Rect playerPos;

    bg = get_ImageCollector(myImageCollector, "lobby/bg")->surface;
    PlayerSprite = get_ImageCollector(myImageCollector, "lobby/player")->surface;


    bgPos.x = 0;
    bgPos.y = 0;
    playerPos.x=data->Isaac->movement->pos->x;
    playerPos.y=data->Isaac->movement->pos->y;

    SDL_BlitSurface(bg, NULL, lobbySurface, &bgPos);

    if(data->lobby->menuHouse == 1){
        SDL_Color black = {0, 0, 0, 0};

        TTF_Font* font1 = NULL;
        font1 = get_FontCollector(myFontCollector, "menu/35")->font;

        TTF_Font* font2 = NULL;
        font2 = get_FontCollector(myFontCollector, "menu/30")->font;

        SDL_Surface* interface = NULL;
        SDL_Surface* menu1x1;
        SDL_Surface* menu1x2;
        SDL_Surface* menu1x3;
        SDL_Surface* menu1xSelec;

        if(data->lobby->askMove == 0){
            interface = get_ImageCollector(myImageCollector, "lobby/menu11")->surface;
        }
        else if (data->lobby->askMove == 1){
            interface = get_ImageCollector(myImageCollector, "lobby/menu12")->surface;
        }
        //interface = get_ImageCollector(myImageCollector, "lobby/menu11")->surface;
        menu1x1 = TTF_RenderText_Solid(font1, "Save Game?", black);
        menu1x2 = TTF_RenderText_Solid(font2, "YES", black);
        menu1x3 = TTF_RenderText_Solid(font2, "NO", black);
        menu1xSelec = TTF_RenderText_Solid(font2, "_______", black);


        SDL_Rect posMenu1x1;
        SDL_Rect posMenu1x2;
        SDL_Rect posMenu1x3;
        SDL_Rect posMenu1x4;
        SDL_Rect posMenu1xInterface;

        posMenu1xInterface.x = (data->Isaac->movement->pos->x)-170;
        posMenu1xInterface.y = (data->Isaac->movement->pos->y)-270;

        posMenu1x1.x = (data->Isaac->movement->pos->x)-50;
        posMenu1x1.y = (data->Isaac->movement->pos->y)-105;

        posMenu1x2.x = posMenu1x1.x-91;
        posMenu1x2.y = posMenu1x1.y-5;

        posMenu1x3.x = posMenu1x1.x+211;
        posMenu1x3.y = posMenu1x1.y-5;

        SDL_BlitSurface(interface, NULL, lobbySurface, &posMenu1xInterface);
        SDL_BlitSurface(menu1x1, NULL, lobbySurface, &posMenu1x1);
        SDL_BlitSurface(menu1x2, NULL, lobbySurface, &posMenu1x2);
        SDL_BlitSurface(menu1x3, NULL, lobbySurface, &posMenu1x3);


    }

    if(data->lobby->menuHouse == 22 ){
        SDL_Color black = {0, 0, 0, 0};

        TTF_Font* font1 = NULL;
        font1 = get_FontCollector(myFontCollector, "menu/35")->font;

        TTF_Font* font2 = NULL;
        font2 = get_FontCollector(myFontCollector, "menu/30")->font;

        SDL_Surface* interface = NULL;
        SDL_Surface* menu1x1;
        SDL_Surface* menu1x2;
        SDL_Surface* menu1x3;

        if(data->lobby->askMove == 0){
            interface = get_ImageCollector(myImageCollector, "lobby/menu11")->surface;
        }
        else if (data->lobby->askMove == 1){
            interface = get_ImageCollector(myImageCollector, "lobby/menu12")->surface;
        }

        menu1x1 = TTF_RenderText_Solid(font1, "Save Game?", black);
        menu1x2 = TTF_RenderText_Solid(font2, "YES", black);
        menu1x3 = TTF_RenderText_Solid(font2, "NO", black);


        SDL_Rect posMenu1x1;
        SDL_Rect posMenu1x2;
        SDL_Rect posMenu1x3;
        SDL_Rect posMenu1x4;
        SDL_Rect posMenu1xInterface;

        posMenu1xInterface.x = (data->Isaac->movement->pos->x)-170;
        posMenu1xInterface.y = (data->Isaac->movement->pos->y)-270;

        posMenu1x1.x = (data->Isaac->movement->pos->x)-50;
        posMenu1x1.y = (data->Isaac->movement->pos->y)-105;

        posMenu1x2.x = posMenu1x1.x-91;
        posMenu1x2.y = posMenu1x1.y-5;

        posMenu1x3.x = posMenu1x1.x+211;
        posMenu1x3.y = posMenu1x1.y-5;

        SDL_BlitSurface(interface, NULL, lobbySurface, &posMenu1xInterface);
        SDL_BlitSurface(menu1x1, NULL, lobbySurface, &posMenu1x1);
        SDL_BlitSurface(menu1x2, NULL, lobbySurface, &posMenu1x2);
        SDL_BlitSurface(menu1x3, NULL, lobbySurface, &posMenu1x3);


    }


    SDL_BlitSurface(PlayerSprite, data->Isaac->movement->SpriteBox, lobbySurface, &playerPos);

    return lobbySurface;
}



extern void renderScene_Scene_lobby(SDL_Surface* window, Engine* engine, Data* data) {
    SDL_Surface* lobbySurface = NULL;
    lobbySurface = getLobby(engine->imageCollector,engine->fontCollector,data);

    SDL_Rect lobbySurfacePos;
    lobbySurfacePos.x = 0;
    lobbySurfacePos.y = 0;

    loadSurface(lobbySurface, window, lobbySurfacePos);

    SDL_FreeSurface(lobbySurface);
}
