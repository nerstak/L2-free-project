#include "render.h"
#include "../../window.h"

static SDL_Surface* getShop(ImageCollector* myImageCollector, FontCollector* myFontCollector, Data* data);

static SDL_Surface* getShop(ImageCollector* myImageCollector, FontCollector* myFontCollector, Data* data) {
    SDL_Surface* shop = NULL;
    shop = SDL_CreateRGBSurface(SDL_HWSURFACE, 1280, 720, 32, 0, 0, 0, 0);

    SDL_Surface* bg = NULL;

    SDL_Surface* moneyInfo = NULL;
    SDL_Surface* dialog1Info = NULL;
    SDL_Surface* dialog2Info = NULL;
    SDL_Surface* shopInfo = NULL;
    SDL_Surface* inventoryInfo = NULL;

    SDL_Surface* selector = NULL;

    TTF_Font* font1 = NULL;

    font1 = get_FontCollector(myFontCollector, "menu/40")->font;
    SDL_Color black = {0, 0, 0, 0};
    SDL_Color white = {255, 255, 255, 0};

    SDL_Rect bgPos;

    SDL_Rect moneyInfoPos;
    SDL_Rect dialog1InfoPos;
    SDL_Rect dialog2InfoPos;
    SDL_Rect shopInfoPos;
    SDL_Rect inventoryInfoPos;

    SDL_Rect selectorPos;

    bg = get_ImageCollector(myImageCollector, "shop/interface")->surface;

    char dialog[200];
    sprintf(dialog, "%s. That costs %d$. I've %d of them in stock...",data->shop->selected->name_item, data->shop->selected->price, data->shop->selected->quantity);
    dialog1Info = TTF_RenderText_Solid(font1, dialog , white);
    sprintf(dialog,"%s",data->shop->selected->description);
    dialog2Info = TTF_RenderText_Solid(font1, dialog , white);
    sprintf(dialog,"%d",data->Isaac->money);
    moneyInfo = TTF_RenderText_Solid(font1, dialog, white);
    shopInfo = TTF_RenderText_Solid(font1, "Shop", black);
    inventoryInfo = TTF_RenderText_Solid(font1, "Inventory", black);

    bgPos.x = 0;
    bgPos.y = 0;

    moneyInfoPos.x = 1000;
    moneyInfoPos.y = 70;

    dialog1InfoPos.x = 46;
    dialog1InfoPos.y = 500;

    dialog2InfoPos.x = 46;
    dialog2InfoPos.y = 540;

    shopInfoPos.x = 85;
    shopInfoPos.y = 15;

    inventoryInfoPos.x = 85;
    inventoryInfoPos.y = 260;

    selectorPos.x = 65 + (data->shop->n_selected % 10) * 77;
    selectorPos.y = 73 + (data->shop->n_selected / 10) * 77 + (data->shop->n_selected / 20) * 90;
    selector = get_ImageCollector(myImageCollector, "shop/cursor")->surface;

    SDL_BlitSurface(bg, NULL, shop, &bgPos);

    SDL_BlitSurface(dialog1Info, NULL, shop, &dialog1InfoPos);
    SDL_BlitSurface(dialog2Info, NULL, shop, &dialog2InfoPos);
    SDL_BlitSurface(moneyInfo, NULL, shop, &moneyInfoPos);
    SDL_BlitSurface(shopInfo, NULL, shop, &shopInfoPos);
    SDL_BlitSurface(inventoryInfo, NULL, shop, &inventoryInfoPos);
    SDL_BlitSurface(selector, NULL, shop, &selectorPos);

    SDL_FreeSurface(moneyInfo);
    SDL_FreeSurface(dialog1Info);
    SDL_FreeSurface(dialog2Info);
    SDL_FreeSurface(shopInfo);
    SDL_FreeSurface(inventoryInfo);

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