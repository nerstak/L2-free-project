#ifndef FREE_PROJECT_ENGINE_COLLECTORS_TTF_H
#define FREE_PROJECT_ENGINE_COLLECTORS_TTF_H

#include <SDL/SDL_ttf.h>

typedef struct Font {
    char name[255];
    TTF_Font* font;

    struct Font* next;
} Font;

typedef  struct FontCollector {
    size_t size;
    Font* fonts;
} FontCollector;

extern FontCollector* init_FontCollector();
extern void clean_FontCollector(FontCollector** myFontCollector);

extern void load_FontCollector(FontCollector* myFontCollector, const char path[], const int size, const char name[]);
extern void unload_FontCollector(FontCollector* myFontCollector, const char name[]);

extern Font* get_FontCollector(FontCollector* myFontCollector, const char name[]);

extern int getWidth_FontCollector(TTF_Font* font, const char str[]);
extern int getHeight_FontCollector(TTF_Font* font, const char str[]);

#endif //FREE_PROJECT_ENGINE_COLLECTORS_TTF_H
