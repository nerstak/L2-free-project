#include "render.h"
#include "../../engine/config.h"
#include "../../window.h"

static SDL_Surface* getOptions(ImageCollector* myImageCollector, FontCollector* myFontCollector, Data* data, Engine* engine);
static void nameKeys(int id, char* name);

static SDL_Surface* getOptions(ImageCollector* myImageCollector, FontCollector* myFontCollector, Data* data, Engine* engine) {
    SDL_Surface* options = NULL;
    options = SDL_CreateRGBSurface(SDL_HWSURFACE, 1280, 720, 32, 0, 0, 0, 0);
    char line[50], name[15];

    //Init surfaces
    SDL_Surface* bg = NULL;
    SDL_Rect bgPos;

    SDL_Surface* bgBlur = NULL;

    SDL_Surface* selection = NULL;
    SDL_Rect selectionPos;

    SDL_Surface* text = NULL;
    SDL_Rect textPos;

    SDL_Surface* player = NULL;
    SDL_Rect playerPos;

    bg = get_ImageCollector(myImageCollector, "options/main_bg")->surface;
    selection = get_ImageCollector(myImageCollector, "options/selection")->surface;
    if(strcmp(engine->sceneCollector->previousScene->name,"mainMenu") == 0) {
        bgBlur = get_ImageCollector(myImageCollector, "options/mainMenu_blur")->surface;
    } else if (strcmp(engine->sceneCollector->previousScene->name,"lobby") == 0) {
        bgBlur = get_ImageCollector(myImageCollector, "options/lobby_blur")->surface;
        player = get_ImageCollector(myImageCollector, "options/player_blur")->surface;
    }

    TTF_Font* font1 = NULL;
    font1 = get_FontCollector(myFontCollector, "menu/20")->font;
    SDL_Color black = {0, 0, 0, 0};


    //Background blit
    bgPos.x = 0;
    bgPos.y = 0;

    SDL_BlitSurface(bgBlur, NULL, options, &bgPos);

    if(strcmp(engine->sceneCollector->previousScene->name,"lobby") == 0) {
        playerPos.x = data->Isaac->movement->pos->x;
        playerPos.y = data->Isaac->movement->pos->y;
        SDL_BlitSurface(player, data->Isaac->movement->SpriteBox, options, &playerPos);

    }

    SDL_BlitSurface(bg, NULL, options, &bgPos);

    //Key blit
    for(int i=0; i < 12; i++) {
        if(data->options->isKeyChanging == 1 && data->options->nSelected == i) {
            strcpy(line,". . .");
        } else {
            nameKeys(findKeyID(engine->keys,i),name);
            sprintf(line, "%s", name);
        }
        text = TTF_RenderText_Solid(font1,line,black);

        textPos.x = 554 + (i % 2) * 264;
        textPos.y = 375 + (i / 2) * 40;

        SDL_BlitSurface(text, NULL, options, &textPos);
    }

    //Selection blit
    if(data->options->nTypeSelected != 3) {
        selectionPos.x = 563 + (data->options->nSelected) * 80;
        selectionPos.y = 198 + (data->options->nTypeSelected) * 60;
    } else {
        selectionPos.x = 544 + (data->options->nSelected % 2) * 264;
        selectionPos.y = 374 + (data->options->nSelected / 2) * 40;
    }

    SDL_BlitSurface(selection, NULL, options, &selectionPos);

    return options;
}

extern void renderScene_Scene_options(SDL_Surface* window, Engine* engine, Data* data) {
    SDL_Surface* optionsSurface = NULL;
    optionsSurface = getOptions(engine->imageCollector, engine->fontCollector, data, engine);

    SDL_Rect optionsSurfacePos;
    optionsSurfacePos.x = 0;
    optionsSurfacePos.y = 0;

    applySurface_Window(optionsSurface, window, optionsSurfacePos);

    SDL_FreeSurface(optionsSurface);
}

static void nameKeys(int id, char* name) {
    strcpy(name,SDL_GetKeyName(id));
    switch(id) {
        case 8: {
            strcpy(name,"Bspace");
            break;
        }
        case 127: {
            strcpy(name, "Del.");
            break;
        }
        case 280: {
            strcpy(name, "Page D");
            break;
        }
        case 281: {
            strcpy(name, "Page U");
            break;
        }
        case 300: {
            strcpy(name, "NumLo");
            break;
        }
        case 301: {
            strcpy(name, "CapsLo");
            break;
        }
        case 302: {
            strcpy(name, "ScroLo");
            break;
        }
        case 303: {
            strcpy(name, "RShift");
            break;
        }
        case 304: {
            strcpy(name, "LShift");
            break;
        }
        case 305: {
            strcpy(name, "R ctrl");
            break;
        }
        case 306: {
            strcpy(name, "L ctrl");
            break;
        }
        case 307: {
            strcpy(name, "R alt");
            break;
        }
        case 308: {
            strcpy(name, "L alt");
            break;
        }
        case 309: {
            strcpy(name, "R meta");
            break;
        }
        case 310: {
            strcpy(name, "L meta");
            break;
        }
        case 311: {
            strcpy(name, "L sup");
            break;
        }
        case 312: {
            strcpy(name, "R sup");
            break;
        }
        case 314: {
            strcpy(name, "Compo");
            break;
        }
        case 316: {
            strcpy(name, "Print");
            break;
        }
        case 317: {
            strcpy(name, "SysReq");
            break;
        }
        default:
            break;
    }
}