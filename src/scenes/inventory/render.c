#include "render.h"
#include "../../window.h"

static SDL_Surface* getInventory(ImageCollector* myImageCollector, FontCollector* myFontCollector, Data* data, Engine* engine);

static void backgroundBlit(Data* data, Engine* engine, ImageCollector* myImageCollector, SDL_Surface* inventory);
static void dialogBlit(Data* data, SDL_Surface* inventory, TTF_Font* font1);
static void infosBlit(Data* data, SDL_Surface* inventory, TTF_Font* font2);
static void effectsBlit(Data* data, ImageCollector* myImageCollector, SDL_Surface* inventory);
static void framesBlit(Data* data, ImageCollector* myImageCollector, SDL_Surface* inventory);
static void confirmationBlit(Data* data, ImageCollector* myImageCollector, SDL_Surface* inventory, TTF_Font* font1, TTF_Font* font2);
static void itemsBlit(Data* data, ImageCollector* myImageCollector, SDL_Surface* inventory);


static SDL_Surface* getInventory(ImageCollector* myImageCollector, FontCollector* myFontCollector, Data* data, Engine* engine) {
    SDL_Surface* inventory = NULL;
    inventory = SDL_CreateRGBSurface(SDL_HWSURFACE, 1280, 720, 32, 0, 0, 0, 0);

    //Font init
    TTF_Font* font20 = NULL;
    font20 = get_FontCollector(myFontCollector, "menu/20")->font;
    TTF_Font* font40 = NULL;
    font40 = get_FontCollector(myFontCollector, "menu/40")->font;
    TTF_Font* font25 = NULL;
    font25 = get_FontCollector(myFontCollector, "menu/25")->font;

    backgroundBlit(data, engine, myImageCollector, inventory);

    dialogBlit(data,inventory, font20);
    infosBlit(data, inventory, font40);

    effectsBlit(data, myImageCollector, inventory);

    framesBlit(data,myImageCollector, inventory);

    //Items blit
    itemsBlit(data, myImageCollector,inventory);

    //Confirmation box blit
    confirmationBlit(data, myImageCollector, inventory, font20, font25);

    return inventory;
}

extern void renderScene_Scene_inventory(SDL_Surface* window, Engine* engine, Data* data) {
    SDL_Surface* mainInventorySurface = NULL;
    mainInventorySurface = getInventory(engine->imageCollector, engine->fontCollector, data, engine);

    SDL_Rect mainInventorySurfacePos;
    mainInventorySurfacePos.x = 0;
    mainInventorySurfacePos.y = 0;

    applySurface_Window(mainInventorySurface, window, mainInventorySurfacePos);

    SDL_FreeSurface(mainInventorySurface);
}

static void backgroundBlit(Data* data, Engine* engine, ImageCollector* myImageCollector, SDL_Surface* inventory) {
    SDL_Surface* layout = NULL;
    SDL_Rect layoutPos;

    SDL_Surface* bgBlur = NULL;

    SDL_Surface* player = NULL;
    SDL_Rect playerPos;
    
    
    layoutPos.x = 0;
    layoutPos.y = 0;

    layout = get_ImageCollector(myImageCollector, "inventory/interface")->surface;
    if (strcmp(engine->sceneCollector->previousScene->name,"lobby") == 0) {
        bgBlur = get_ImageCollector(myImageCollector, "inventory/lobby_blur")->surface;
        player = get_ImageCollector(myImageCollector, "inventory/player_blur")->surface;
    }

    SDL_BlitSurface(bgBlur, NULL, inventory, &layoutPos);

    if(strcmp(engine->sceneCollector->previousScene->name,"lobby") == 0) {
        playerPos.x = data->Isaac->movement->pos->x;
        playerPos.y = data->Isaac->movement->pos->y;
        SDL_BlitSurface(player, data->Isaac->movement->SpriteBox, inventory, &playerPos);
    }

    SDL_BlitSurface(layout, NULL, inventory, &layoutPos);
}

static void dialogBlit(Data* data, SDL_Surface* inventory, TTF_Font* font1) {
    char dialog[200];
    SDL_Color almostBlack = {20, 15, 25, 0};
    SDL_Surface* dialogInfo = NULL;
    SDL_Rect dialogInfoPos;

    if(data->inventory->selected != NULL && !isStarted_Timer(data->inventory->timerMessage)) {
        //Informations of the item
        for(int i = 0; i < 3; i++) {
            switch (i) {
                case 0: {
                    sprintf(dialog, "%s.",data->inventory->selected->name);
                    break;
                }
                case 1: {
                    sprintf(dialog, "%s",data->inventory->selected->description);
                    break;
                }
                case 2: {
                    sprintf(dialog, "This is worth %d$, and I've %d of those.",(int)(data->inventory->selected->price * .8),data->inventory->selected->quantity);
                    break;
                }
            }
            dialogInfo = TTF_RenderText_Solid(font1, dialog, almostBlack);

            dialogInfoPos.x = 152;
            dialogInfoPos.y = 547 + i * 34;

            SDL_BlitSurface(dialogInfo, NULL, inventory, &dialogInfoPos);
        }
    } else if(isStarted_Timer(data->inventory->timerMessage)) {
        strcpy(dialog, data->inventory->messageUsed);
        dialogInfo = TTF_RenderText_Solid(font1, dialog, almostBlack);

        dialogInfoPos.x = 152;
        dialogInfoPos.y = 547;

        SDL_BlitSurface(dialogInfo, NULL, inventory, &dialogInfoPos);
    }
    SDL_FreeSurface(dialogInfo);
}

static void infosBlit(Data* data, SDL_Surface* inventory, TTF_Font* font2) {
    char dialog[200];
    SDL_Color almostBlack = {20, 15, 25, 0};
    SDL_Surface* dialogInfo = NULL;
    SDL_Rect dialogInfoPos;

    for(int i = 0; i < 2; i++) {
        int coordX;
        if(i == 0) {
            sprintf(dialog,"%d",data->Isaac->money);
            coordX = 875;
        } else {
            sprintf(dialog,"%d",data->Isaac->gameStats->dungeons);
            coordX = 965;
        }
        dialogInfo = TTF_RenderText_Solid(font2, dialog, almostBlack);

        dialogInfoPos.x = (Sint16) (coordX + ((75 / 2) - (getWidth_FontCollector(font2, dialog) / 2)));
        dialogInfoPos.y = (Sint16) (535 + ((75 / 2) - (getHeight_FontCollector(font2, dialog) / 2)));


        SDL_BlitSurface(dialogInfo, NULL, inventory, &dialogInfoPos);
    }
    SDL_FreeSurface(dialogInfo);
}

static void effectsBlit(Data* data, ImageCollector* myImageCollector, SDL_Surface* inventory) {
    SDL_Surface* effect = NULL;
    SDL_Rect effectPos;
    SDL_Rect effectSize;

    effect = get_ImageCollector(myImageCollector, "inventory/effects")->surface;

    effectSize.h = 32;
    effectSize.w = 32;
    for(int i = 0; i < 6; i++) {
        if(data->Isaac->stats->potionsUsed[i] == 1) {
            effectSize.x = i * 32;
            effectSize.y = 0;
            effectPos.x = 775;
            effectPos.y = 82 + i * 38;

            SDL_BlitSurface(effect, &effectSize, inventory, &effectPos);
        }
    }
}

static void framesBlit(Data* data, ImageCollector* myImageCollector, SDL_Surface* inventory) {
    SDL_Surface* frame = NULL;
    SDL_Surface* frameSelected = NULL;
    SDL_Rect framePos;

    frame = get_ImageCollector(myImageCollector, "inventory/frame")->surface;
    frameSelected = get_ImageCollector(myImageCollector, "inventory/frameSelected")->surface;

    for(int i = 0; i < data->Isaac->size_inventory; i++) {
        framePos.x = 139 + (i % 4) * 123;
        framePos.y = 121 + (i / 4) * 108;
        if(i == data->inventory->nSelected) {
            SDL_BlitSurface(frameSelected, NULL, inventory, &framePos);
        } else {
            SDL_BlitSurface(frame, NULL, inventory, &framePos);
        }
    }
}

static void confirmationBlit(Data* data, ImageCollector* myImageCollector, SDL_Surface* inventory, TTF_Font* font1, TTF_Font* font2) {
    char dialog[200];
    SDL_Color almostBlack = {20, 15, 25, 0};
    SDL_Surface* dialogInfo = NULL;
    SDL_Rect dialogInfoPos;
    TTF_Font* currentFont;

    SDL_Surface* confirm = NULL;
    SDL_Rect confirmPos;

    confirm = get_ImageCollector(myImageCollector, "inventory/confirm")->surface;

    if(data->inventory->askDeletion != -1 && data->inventory->selected != NULL) {
        confirmPos.x = 0;
        confirmPos.y = 0;
        SDL_BlitSurface(confirm, NULL, inventory, &confirmPos);
        for(int i = 0; i < 4; i++) {
            switch (i) {
                case 0: {
                    currentFont = font2;
                    sprintf(dialog, "Are you sure you want to delete it?");
                    dialogInfoPos.x = 460 + ((360 / 2) - (getWidth_FontCollector(currentFont, dialog) / 2));
                    dialogInfoPos.y = 280;
                    break;
                }
                case 1: {
                    currentFont = font1;
                    strcpy(dialog, "Confirm");
                    dialogInfoPos.x = 512;
                    dialogInfoPos.y = 425;
                    if (data->inventory->askDeletion == 1) {
                        TTF_SetFontStyle(currentFont, TTF_STYLE_UNDERLINE);
                    }
                    break;
                }
                case 2: {
                    currentFont = font1;
                    strcpy(dialog, "Cancel");
                    dialogInfoPos.x = 700;
                    dialogInfoPos.y = 425;
                    if (data->inventory->askDeletion == 0) {
                        TTF_SetFontStyle(currentFont, TTF_STYLE_UNDERLINE);
                    }
                    break;
                }
            }
            dialogInfo = TTF_RenderText_Solid(currentFont, dialog, almostBlack);
            SDL_BlitSurface(dialogInfo, NULL, inventory, &dialogInfoPos);
            TTF_SetFontStyle(currentFont, TTF_STYLE_NORMAL);
        }
    }
    SDL_FreeSurface(dialogInfo);
}

static void itemsBlit(Data* data, ImageCollector* myImageCollector, SDL_Surface* inventory) {
    SDL_Surface* item = NULL;
    SDL_Rect itemPos;
    SDL_Rect itemSize;

    SlotInventory* tempItem;

    item = get_ImageCollector(myImageCollector, "inventory/items")->surface;

    itemSize.h = 64;
    itemSize.w = 64;
    tempItem = data->Isaac->inventory;
    for(int i = 0; i < data->Isaac->size_inventory; i++) {
        if(tempItem) {
            itemSize.x = (tempItem->id % 5) * 64;
            itemSize.y = (tempItem->id / 5) * 64;
            itemPos.x = 155 + (i % 4) * 123;
            itemPos.y = 100 + (i / 4) * 108;
            SDL_BlitSurface(item, &itemSize, inventory, &itemPos);
            tempItem = tempItem->next;
        }
    }
}