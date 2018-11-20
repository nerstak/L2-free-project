#include "render.h"
#include "../../window.h"

static SDL_Surface* getShop(ImageCollector* myImageCollector, FontCollector* myFontCollector, Data* data);

static SDL_Surface* getShop(ImageCollector* myImageCollector, FontCollector* myFontCollector, Data* data) {
    SDL_Surface* shop = NULL;
    shop = SDL_CreateRGBSurface(SDL_HWSURFACE, 1280, 720, 32, 0, 0, 0, 0);
    char dialog[200];

    //Font init
    TTF_Font* font1 = NULL;
    font1 = get_FontCollector(myFontCollector, "menu/20")->font;
    TTF_Font* font2 = NULL;
    font2 = get_FontCollector(myFontCollector, "menu/40")->font;
    SDL_Color black = {0, 0, 0, 0};
    SDL_Color white = {255, 255, 255, 0};

    //Surfaces init
    SDL_Surface* layout = NULL;
    SDL_Rect layoutPos;

    SDL_Surface* dialogInfo = NULL;
    SDL_Rect dialogInfoPos;

    SDL_Surface* frame = NULL;
    SDL_Surface* frameSelected = NULL;
    SDL_Rect framePos;

    layout = get_ImageCollector(myImageCollector, "shop/interface")->surface;
    frame = get_ImageCollector(myImageCollector, "shop/frame")->surface;
    frameSelected = get_ImageCollector(myImageCollector, "shop/frameSelected")->surface;

    //Layout blit
    layoutPos.x = 0;
    layoutPos.y = 0;
    SDL_BlitSurface(layout, NULL, shop, &layoutPos);

    //DialogBox blit
    if(data->shop->selected != NULL) {
        //Informations of the item
        for(int i = 0; i < 3; i++) {
            switch (i) {
                case 0: {
                    sprintf(dialog, "%s.",data->shop->selected->name);
                    break;
                }
                case 1: {
                    sprintf(dialog, "%s.",data->shop->selected->description);
                    break;
                }
                case 2: {
                    sprintf(dialog, "This is worth %d$, and I've %d of those.",data->shop->selected->price,data->shop->selected->quantity);
                    break;
                }
                default: break;
            }
            dialogInfo = TTF_RenderText_Solid(font1, dialog, black);

            dialogInfoPos.x = 80;
            dialogInfoPos.y = 550 + i * 34;

            SDL_BlitSurface(dialogInfo, NULL, shop, &dialogInfoPos);
        }
    }


    //Money Blit
    sprintf(dialog,"%d",data->Isaac->money);
    dialogInfo = TTF_RenderText_Solid(font2, dialog, black);

    dialogInfoPos.x = 600;
    dialogInfoPos.y = 430;

    SDL_BlitSurface(dialogInfo, NULL, shop, &dialogInfoPos);



    //Frames inventory blit
    for(int i = 0; i < data->Isaac->size_inventory; i++) {
        framePos.x = 47 + (i % 4) * 123;
        framePos.y = 118 + (i / 4) * 108;
        if(i == data->shop->nSelected) {
            SDL_BlitSurface(frameSelected, NULL, shop, &framePos);
        } else {
            SDL_BlitSurface(frame, NULL, shop, &framePos);
        }
    }

    //Frames shop blit
    for(int i = 0; i < data->shop->size_shop; i++) {
        framePos.x = 755 + (i % 4) * 123;
        framePos.y = 118 + (i / 4) * 108;
        if(i + 16 == data->shop->nSelected) {
            SDL_BlitSurface(frameSelected, NULL, shop, &framePos);
        } else {
            SDL_BlitSurface(frame, NULL, shop, &framePos);
        }
    }

    //TODO: Fix segfault due to those free

    SDL_FreeSurface(dialogInfo);

    return shop;
}

extern void renderScene_Scene_shop(SDL_Surface* window, Engine* engine, Data* data) {
    SDL_Surface* mainShopSurface = NULL;
    mainShopSurface = getShop(engine->imageCollector, engine->fontCollector, data);

    SDL_Rect mainShopSurfacePos;
    mainShopSurfacePos.x = 0;
    mainShopSurfacePos.y = 0;

    loadSurface(mainShopSurface, window, mainShopSurfacePos);

    SDL_FreeSurface(mainShopSurface);
}