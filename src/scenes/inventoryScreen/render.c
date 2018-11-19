#include "render.h"
#include "../../window.h"

static SDL_Surface* getInventory(ImageCollector* myImageCollector, FontCollector* myFontCollector, Data* data);

static SDL_Surface* getInventory(ImageCollector* myImageCollector, FontCollector* myFontCollector, Data* data) {
    SDL_Surface* inventory = NULL;
    inventory = SDL_CreateRGBSurface(SDL_HWSURFACE, 1280, 720, 32, 0, 0, 0, 0);
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

    layout = get_ImageCollector(myImageCollector, "inventory/interface")->surface;
    frame = get_ImageCollector(myImageCollector, "inventory/frame")->surface;
    frameSelected = get_ImageCollector(myImageCollector, "inventory/frameSelected")->surface;

    //Layout blit
    layoutPos.x = 0;
    layoutPos.y = 0;
    SDL_BlitSurface(layout, NULL, inventory, &layoutPos);

    //DialogBox blit
    for(int i = 0; i < 3; i++) {
        switch (i) {
            case 0: {
                sprintf(dialog, "%s.",data->inventory->selected->name);
                break;
            }
            case 1: {
                sprintf(dialog, "%s.",data->inventory->selected->description);
                break;
            }
            case 2: {
                sprintf(dialog, "This is worth %d$, and I've %d of those.",data->inventory->selected->price,data->inventory->selected->quantity);
                break;
            }
        }
        dialogInfo = TTF_RenderText_Solid(font1, dialog, black);

        dialogInfoPos.x = 152;
        dialogInfoPos.y = 547 + i * 34;

        SDL_BlitSurface(dialogInfo, NULL, inventory, &dialogInfoPos);
    }

    //Money Blit
    sprintf(dialog,"%d",data->Isaac->money);
    dialogInfo = TTF_RenderText_Solid(font2, dialog, black);

    dialogInfoPos.x = 880;
    dialogInfoPos.y = 550;

    SDL_BlitSurface(dialogInfo, NULL, inventory, &dialogInfoPos);



    //Frames blit
    for(int i = 0; i < data->Isaac->size_inventory; i++) {
        framePos.x = 139 + (i % 4) * 123;
        framePos.y = 121 + (i / 4) * 108;
        if(i == data->inventory->nSelected) {
            SDL_BlitSurface(frameSelected, NULL, inventory, &framePos);
        } else {
            SDL_BlitSurface(frame, NULL, inventory, &framePos);
        }
    }

    return inventory;
}

extern void renderScene_Scene_inventory(SDL_Surface* window, Engine* engine, Data* data) {
    SDL_Surface* mainInventorySurface = NULL;
    mainInventorySurface = getInventory(engine->imageCollector, engine->fontCollector, data);

    SDL_Rect mainInventorySurfacePos;
    mainInventorySurfacePos.x = 0;
    mainInventorySurfacePos.y = 0;

    loadSurface(mainInventorySurface, window, mainInventorySurfacePos);

    SDL_FreeSurface(mainInventorySurface);
}