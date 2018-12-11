#include "render.h"
#include "../../window.h"

static SDL_Surface* getShop(ImageCollector* myImageCollector, FontCollector* myFontCollector, Data* data, Engine* engine);

static void backgroundBlit(Data* data, Engine* engine, ImageCollector* myImageCollector, SDL_Surface* shop);
static void dialogBlit(Data* data, SDL_Surface* shop, TTF_Font* font1);
static void infoItemBlit(Data* data, SDL_Surface* shop, TTF_Font* font1);
static void transactionBlit(Data* data, SDL_Surface* shop, TTF_Font* font1);
static void moneyBlit(Data* data, SDL_Surface* shop, TTF_Font* font2);
static void framesBlit(Data* data, ImageCollector* myImageCollector, SDL_Surface* shop, TTF_Font* font1);
static void itemsBlit(Data* data, ImageCollector* myImageCollector, SDL_Surface* shop, TTF_Font* font1);
static void confirmationBlit(Data* data, ImageCollector* myImageCollector, SDL_Surface* shop, TTF_Font* font1, TTF_Font* font2);

static SDL_Surface* getShop(ImageCollector* myImageCollector, FontCollector* myFontCollector, Data* data, Engine* engine) {
    SDL_Surface* shop = NULL;
    shop = SDL_CreateRGBSurface(SDL_HWSURFACE, 1280, 720, 32, 0, 0, 0, 0);

    //Font init
    TTF_Font* font30 = NULL;
    font30 = get_FontCollector(myFontCollector, "menu/30")->font;
    TTF_Font* font40 = NULL;
    font40 = get_FontCollector(myFontCollector, "menu/40")->font;
    TTF_Font* font20 = NULL;
    font20 = get_FontCollector(myFontCollector, "menu/20")->font;
    TTF_Font* font25 = NULL;
    font25 = get_FontCollector(myFontCollector, "menu/25")->font;

    backgroundBlit(data, engine, myImageCollector, shop);

    dialogBlit(data, shop, font30);
    moneyBlit(data, shop, font40);

    framesBlit(data, myImageCollector, shop, font30);
    itemsBlit(data, myImageCollector, shop, font30);

    confirmationBlit(data, myImageCollector, shop, font20, font25);

    return shop;
}

extern void renderScene_Scene_shop(SDL_Surface* window, Engine* engine, Data* data) {
    SDL_Surface* mainShopSurface = NULL;
    mainShopSurface = getShop(engine->imageCollector, engine->fontCollector, data, engine);

    SDL_Rect mainShopSurfacePos;
    mainShopSurfacePos.x = 0;
    mainShopSurfacePos.y = 0;

    applySurface_Window(mainShopSurface, window, mainShopSurfacePos);

    SDL_FreeSurface(mainShopSurface);
}


static void backgroundBlit(Data* data, Engine* engine, ImageCollector* myImageCollector, SDL_Surface* shop) {
    //Surfaces init
    SDL_Surface* layout = NULL;
    SDL_Rect layoutPos;

    SDL_Surface* bgBlur = NULL;


    SDL_Surface* player = NULL;
    SDL_Rect playerPos;

    layout = get_ImageCollector(myImageCollector, "shop/interface")->surface;
    if (strcmp(engine->sceneCollector->previousScene->name,"lobby") == 0) {
        bgBlur = get_ImageCollector(myImageCollector, "shop/lobby_blur")->surface;
        player = get_ImageCollector(myImageCollector, "shop/player_blur")->surface;
    }

    //Layout blit
    layoutPos.x = 0;
    layoutPos.y = 0;

    SDL_BlitSurface(bgBlur, NULL, shop, &layoutPos);
    plantsBlit(shop, data, myImageCollector, 'b');

    if(strcmp(engine->sceneCollector->previousScene->name,"lobby") == 0) {
        playerPos.x = data->Isaac->movement->position->x;
        playerPos.y = data->Isaac->movement->position->y;
        SDL_BlitSurface(player, data->Isaac->movement->spriteBox, shop, &playerPos);
    }

    SDL_BlitSurface(layout, NULL, shop, &layoutPos);
}



static void dialogBlit(Data* data, SDL_Surface* shop, TTF_Font* font1) {
    if(data->shop->selected != NULL && !isStarted_Timer(data->shop->timerMessage)) {
        infoItemBlit(data, shop, font1);
    } else if(isStarted_Timer(data->shop->timerMessage)) {
        transactionBlit(data, shop, font1);
    }
}

static void infoItemBlit(Data* data, SDL_Surface* shop, TTF_Font* font1) {
    //Informations of the item
    SDL_Surface* dialogInfo = NULL;
    SDL_Rect dialogInfoPos;
    SDL_Color almostBlack = {20, 15, 25, 0};
    SDL_Color white = {171, 171, 171, 0};
    SDL_Color currentColor;
    char dialog[200];

    for(int i = 0; i < 3; i++) {
        switch (i) {
            case 0: {
                //First line
                if(data->shop->nSelected < 16) {
                    sprintf(dialog, "Oh... %s. Interesting.",data->shop->selected->name);
                } else {
                    sprintf(dialog, "This is a %s.",data->shop->selected->name);
                }
                currentColor = almostBlack;
                break;
            }
            case 1: {
                //Second line
                sprintf(dialog, "%s",data->shop->selected->description);
                currentColor = almostBlack;
                break;
            }
            case 2: {
                //Third line
                if(data->shop->nSelected < 16) {
                    sprintf(dialog, "You have %d of those. I can give you %d$/piece.",data->shop->selected->quantity,(int)(data->shop->selected->price * .8));
                } else {
                    sprintf(dialog, "This is worth %d$. Deal?",data->shop->selected->price);
                }
                currentColor = white;
                break;
            }
            default: break;
        }
        dialogInfo = TTF_RenderText_Solid(font1, dialog, currentColor);

        dialogInfoPos.x = 80;
        dialogInfoPos.y = 550 + i * 50;

        SDL_BlitSurface(dialogInfo, NULL, shop, &dialogInfoPos);
    }
    SDL_FreeSurface(dialogInfo);
}

static void transactionBlit(Data* data, SDL_Surface* shop, TTF_Font* font1) {
    SDL_Surface* dialogInfo = NULL;
    SDL_Rect dialogInfoPos;
    SDL_Color almostBlack = {20, 15, 25, 0};
    char dialog[200];

    if(strcmp(data->shop->messageAction,"Init") != 0) {
        strcpy(dialog, data->shop->messageAction);
        dialogInfo = TTF_RenderText_Solid(font1, dialog, almostBlack);

        dialogInfoPos.x = 80;
        dialogInfoPos.y = 550;

        SDL_BlitSurface(dialogInfo, NULL, shop, &dialogInfoPos);
    } else {
        // Message when entering the shop
        for(int i = 0; i < 3; i++) {
            switch (i) {
                case 0: {
                    //First line
                    strcpy(dialog, "Ooooh, welcome to my modest shop! I'll buy anything you have!");
                    dialogInfo = TTF_RenderText_Solid(font1, dialog, almostBlack);
                    break;
                }
                case 1: {
                    //Second line
                    strcpy(dialog, "If you don't want to eat your harvest and its power, I can take it...");
                    dialogInfo = TTF_RenderText_Solid(font1, dialog, almostBlack);
                    break;
                }
                case 2: {
                    //Third line
                    strcpy(dialog, "And I also have some potions to upgrade your capacities for a day!");
                    dialogInfo = TTF_RenderText_Solid(font1, dialog, almostBlack);
                    break;
                }
                default:
                    break;
            }
            dialogInfoPos.x = 80;
            dialogInfoPos.y = 550 + i * 50;

            SDL_BlitSurface(dialogInfo, NULL, shop, &dialogInfoPos);
        }
    }
    SDL_FreeSurface(dialogInfo);
}

static void moneyBlit(Data* data, SDL_Surface* shop, TTF_Font* font2) {
    SDL_Surface* dialogInfo = NULL;
    SDL_Rect dialogInfoPos;
    SDL_Color almostBlack = {20, 15, 25, 0};
    char dialog[200];

    sprintf(dialog,"%d",data->Isaac->money);
    dialogInfo = TTF_RenderText_Solid(font2, dialog, almostBlack);

    dialogInfoPos.x = (Sint16) (596  + ((87 / 2) - (getWidth_FontCollector(font2, dialog) / 2)));
    dialogInfoPos.y = (Sint16) (439  + ((45 / 2) - (getWidth_FontCollector(font2, dialog) / 2)));

    SDL_BlitSurface(dialogInfo, NULL, shop, &dialogInfoPos);
    SDL_FreeSurface(dialogInfo);
}

static void confirmationBlit(Data* data, ImageCollector* myImageCollector, SDL_Surface* shop, TTF_Font* font1, TTF_Font* font2) {
    SDL_Surface* dialogInfo = NULL;
    SDL_Rect dialogInfoPos;
    SDL_Surface* confirm = NULL;
    SDL_Rect confirmPos;
    TTF_Font* currentFont;

    confirm = get_ImageCollector(myImageCollector, "shop/confirm")->surface;

    SDL_Color almostBlack = {20, 15, 25, 0};
    char dialog[200];
    
    if(data->shop->askTransaction != -1 && data->shop->selected) {
        confirmPos.x = 0;
        confirmPos.y = 0;
        SDL_BlitSurface(confirm, NULL, shop, &confirmPos);
        for(int i = 0; i < 4; i++) {
            switch (i) {
                case 0: {
                    if(data->shop->nSelected < 16) {
                        sprintf(dialog, "How much do you sell to me?");
                    }else {
                        sprintf(dialog, "How much of them do you want?");
                    }
                    currentFont = font2;
                    dialogInfoPos.x = 460 + ((360 / 2) - (getWidth_FontCollector(currentFont, dialog) / 2));
                    dialogInfoPos.y = 280;
                    break;
                }
                case 1: {
                    currentFont = font2;
                    sprintf(dialog, "< %d >", data->shop->itemsInTransaction);
                    dialogInfoPos.x = 460 + ((360 / 2) - (getWidth_FontCollector(currentFont, dialog) / 2));
                    dialogInfoPos.y = 350;
                    if(data->shop->askTransaction == 2) {
                        TTF_SetFontStyle(currentFont, TTF_STYLE_UNDERLINE);
                    }
                    break;
                }
                case 2: {
                    currentFont = font1;
                    strcpy(dialog, "Confirm");
                    dialogInfoPos.x = 512;
                    dialogInfoPos.y = 425;
                    if(data->shop->askTransaction == 1) {
                        TTF_SetFontStyle(currentFont, TTF_STYLE_UNDERLINE);
                    }
                    break;
                }
                case 3: {
                    currentFont = font1;
                    strcpy(dialog, "Cancel");
                    dialogInfoPos.x = 700;
                    dialogInfoPos.y = 425;
                    if(data->shop->askTransaction == 0) {
                        TTF_SetFontStyle(currentFont, TTF_STYLE_UNDERLINE);
                    }
                    break;
                }

            }
            dialogInfo = TTF_RenderText_Solid(currentFont, dialog, almostBlack);
            SDL_BlitSurface(dialogInfo, NULL, shop, &dialogInfoPos);
            TTF_SetFontStyle(currentFont, TTF_STYLE_NORMAL);
        }
    }
    SDL_FreeSurface(dialogInfo);
}

static void framesBlit(Data* data, ImageCollector* myImageCollector, SDL_Surface* shop, TTF_Font* font1) {
    SDL_Surface* frame = NULL;
    SDL_Surface* frameSelected = NULL;
    SDL_Rect framePos;

    frame = get_ImageCollector(myImageCollector, "shop/frame")->surface;
    frameSelected = get_ImageCollector(myImageCollector, "shop/frameSelected")->surface;

    //Frames inventory blit
    for(int i = 0; i < data->Isaac->sizeInventory; i++) {
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
}

static void itemsBlit(Data* data, ImageCollector* myImageCollector, SDL_Surface* shop, TTF_Font* font1) {
    SDL_Surface* item = NULL;
    SDL_Rect itemPos;
    SDL_Rect itemSize;

    SlotInventory* tempItem;

    item = get_ImageCollector(myImageCollector, "shop/items")->surface;

    //Items inventory blit
    itemSize.h = 64;
    itemSize.w = 64;
    tempItem = data->Isaac->inventory;
    for(int i = 0; i < data->Isaac->sizeInventory; i++) {
        if(tempItem) {
            itemSize.x = (tempItem->id % 5) * 64;
            itemSize.y = (tempItem->id / 5) * 64;
            itemPos.x = 62 + (i % 4) * 123;
            itemPos.y = 95 + (i / 4) * 108;
            SDL_BlitSurface(item, &itemSize, shop, &itemPos);
            tempItem = tempItem->next;
        }
    }

    //Items shop blit
    tempItem = data->shop->shop_inv;
    for(int i = 0; i < data->shop->size_shop; i++) {
        if(tempItem) {
            itemSize.x = (tempItem->id % 5) * 64;
            itemSize.y = (tempItem->id / 5) * 64;
            itemPos.x = 772 + (i % 4) * 123;
            itemPos.y = 95 + (i / 4) * 108;
            SDL_BlitSurface(item, &itemSize, shop, &itemPos);
            tempItem = tempItem->next;
        }
    }
}