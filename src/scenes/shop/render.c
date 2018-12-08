#include "render.h"
#include "../../window.h"

static SDL_Surface* getShop(ImageCollector* myImageCollector, FontCollector* myFontCollector, Data* data);

static SDL_Surface* getShop(ImageCollector* myImageCollector, FontCollector* myFontCollector, Data* data) {
    SDL_Surface* shop = NULL;
    shop = SDL_CreateRGBSurface(SDL_HWSURFACE, 1280, 720, 32, 0, 0, 0, 0);
    char dialog[200];
    SlotInventory* tempItem;

    //Font init
    TTF_Font* font1 = NULL;
    font1 = get_FontCollector(myFontCollector, "menu/20")->font;
    TTF_Font* font2 = NULL;
    font2 = get_FontCollector(myFontCollector, "menu/40")->font;
    SDL_Color black = {0, 0, 0, 0};

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

    SDL_Surface* item = NULL;
    SDL_Rect itemPos;
    SDL_Rect itemSize;

    layout = get_ImageCollector(myImageCollector, "shop/interface")->surface;
    frame = get_ImageCollector(myImageCollector, "shop/frame")->surface;
    frameSelected = get_ImageCollector(myImageCollector, "shop/frameSelected")->surface;
    confirm = get_ImageCollector(myImageCollector, "shop/confirm")->surface;
    item = get_ImageCollector(myImageCollector, "shop/items")->surface;

    //Layout blit
    layoutPos.x = 0;
    layoutPos.y = 0;
    SDL_BlitSurface(layout, NULL, shop, &layoutPos);

    //DialogBox blit
    if(data->shop->selected != NULL && !isStarted_Timer(data->shop->timerMessage)) {
        //Informations of the item
        for(int i = 0; i < 3; i++) {
            switch (i) {
                case 0: {
                    if(data->shop->nSelected < 16) {
                        sprintf(dialog, "Oh... %s. Interesting.",data->shop->selected->name);
                    } else {
                        sprintf(dialog, "This is a %s.",data->shop->selected->name);
                    }

                    break;
                }
                case 1: {
                    sprintf(dialog, "%s",data->shop->selected->description);
                    break;
                }
                case 2: {
                    if(data->shop->nSelected < 16) {
                        sprintf(dialog, "You have %d of those. I can give you %d$/piece.",data->shop->selected->quantity,(int)(data->shop->selected->price * .8));
                    } else {
                        sprintf(dialog, "This is worth %d$. Deal?",data->shop->selected->price);
                    }
                    break;
                }
                default: break;
            }
            dialogInfo = TTF_RenderText_Solid(font1, dialog, black);

            dialogInfoPos.x = 80;
            dialogInfoPos.y = 570 + i * 40;

            SDL_BlitSurface(dialogInfo, NULL, shop, &dialogInfoPos);
        }
    } else if(isStarted_Timer(data->shop->timerMessage)) {
        strcpy(dialog, data->shop->messageAction);
        dialogInfo = TTF_RenderText_Solid(font1, dialog, black);

        dialogInfoPos.x = 80;
        dialogInfoPos.y = 570;

        SDL_BlitSurface(dialogInfo, NULL, shop, &dialogInfoPos);
    }


    //Money Blit
    sprintf(dialog,"%d",data->Isaac->money);
    dialogInfo = TTF_RenderText_Solid(font2, dialog, black);

    dialogInfoPos.x = 600;
    dialogInfoPos.y = 430;

    SDL_BlitSurface(dialogInfo, NULL, shop, &dialogInfoPos);



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

    //Confirmation box blit
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
                    dialogInfoPos.x = 515;
                    dialogInfoPos.y = 280;
                    break;
                }
                case 1: {
                    sprintf(dialog, "< %d >", data->shop->itemsInTransaction);
                    dialogInfoPos.x = 624;
                    dialogInfoPos.y = 350;
                    if(data->shop->askTransaction == 2) {
                        TTF_SetFontStyle(font1, TTF_STYLE_UNDERLINE);
                    }
                    break;
                }
                case 2: {
                    strcpy(dialog, "Confirm");
                    dialogInfoPos.x = 512;
                    dialogInfoPos.y = 425;
                    if(data->shop->askTransaction == 1) {
                        TTF_SetFontStyle(font1, TTF_STYLE_UNDERLINE);
                    }
                    break;
                }
                case 3: {
                    strcpy(dialog, "Cancel");
                    dialogInfoPos.x = 700;
                    dialogInfoPos.y = 425;
                    if(data->shop->askTransaction == 0) {
                        TTF_SetFontStyle(font1, TTF_STYLE_UNDERLINE);
                    }
                    break;
                }

            }
            dialogInfo = TTF_RenderText_Solid(font1, dialog, black);
            SDL_BlitSurface(dialogInfo, NULL, shop, &dialogInfoPos);
            TTF_SetFontStyle(font1, TTF_STYLE_NORMAL);
        }
    }
    SDL_FreeSurface(dialogInfo);

    return shop;
}

extern void renderScene_Scene_shop(SDL_Surface* window, Engine* engine, Data* data) {
    SDL_Surface* mainShopSurface = NULL;
    mainShopSurface = getShop(engine->imageCollector, engine->fontCollector, data);

    SDL_Rect mainShopSurfacePos;
    mainShopSurfacePos.x = 0;
    mainShopSurfacePos.y = 0;

    applySurface_Window(mainShopSurface, window, mainShopSurfacePos);

    SDL_FreeSurface(mainShopSurface);
}