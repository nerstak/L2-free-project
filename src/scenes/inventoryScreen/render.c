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

    SDL_Surface* confirm = NULL;
    SDL_Rect confirmPos;

    layout = get_ImageCollector(myImageCollector, "inventory/interface")->surface;
    frame = get_ImageCollector(myImageCollector, "inventory/frame")->surface;
    frameSelected = get_ImageCollector(myImageCollector, "inventory/frameSelected")->surface;
    confirm = get_ImageCollector(myImageCollector, "inventory/confirm")->surface;

    //Layout blit
    layoutPos.x = 0;
    layoutPos.y = 0;
    SDL_BlitSurface(layout, NULL, inventory, &layoutPos);

    //DialogBox blit
    if(data->inventory->selected != NULL && data->inventory->askDeletion == -1) {
        //Informations of the item
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
                    sprintf(dialog, "This is worth %d$, and I've %d of those.",(int)(data->inventory->selected->price * .8),data->inventory->selected->quantity);
                    break;
                }
            }
            dialogInfo = TTF_RenderText_Solid(font1, dialog, black);

            dialogInfoPos.x = 152;
            dialogInfoPos.y = 547 + i * 34;

            SDL_BlitSurface(dialogInfo, NULL, inventory, &dialogInfoPos);
        }
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

    //Confirmation box blit
    if(data->inventory->askDeletion != -1 && data->inventory->selected != NULL) {
        confirmPos.x = 0;
        confirmPos.y = 0;
        SDL_BlitSurface(confirm, NULL, inventory, &confirmPos);
        for(int i = 0; i < 4; i++) {
            switch (i) {
                case 0: {
                    sprintf(dialog, "Are you sure you want to delete it?");
                    dialogInfoPos.x = 515;
                    dialogInfoPos.y = 280;
                    break;
                }
                case 1: {
                    strcpy(dialog, "Confirm");
                    dialogInfoPos.x = 512;
                    dialogInfoPos.y = 425;
                    if (data->inventory->askDeletion == 1) {
                        TTF_SetFontStyle(font1, TTF_STYLE_UNDERLINE);
                    }
                    break;
                }
                case 2: {
                    strcpy(dialog, "Cancel");
                    dialogInfoPos.x = 700;
                    dialogInfoPos.y = 425;
                    if (data->inventory->askDeletion == 0) {
                        TTF_SetFontStyle(font1, TTF_STYLE_UNDERLINE);
                    }
                    break;
                }
            }
            dialogInfo = TTF_RenderText_Solid(font1, dialog, black);
            SDL_BlitSurface(dialogInfo, NULL, inventory, &dialogInfoPos);
            TTF_SetFontStyle(font1, TTF_STYLE_NORMAL);
        }
    }

    SDL_FreeSurface(dialogInfo);

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