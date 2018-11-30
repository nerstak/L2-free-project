#ifndef FREE_PROJECT_ENGINE_COLLECTORS_IMAGE_H
#define FREE_PROJECT_ENGINE_COLLECTORS_IMAGE_H

#include <SDL/SDL_video.h>

#include "../asset.h"

typedef struct Image {
    char name[255];
    SDL_Surface* surface;

    struct Image* next;
} Image;

typedef struct ImageCollector {
    size_t size;
    Image* images;
} ImageCollector;

extern ImageCollector* init_ImageCollector();
extern void clean_ImageCollector(ImageCollector** myImageCollector);

extern void load_ImageCollector(ImageCollector* myImageCollector, const char path[], const char name[]);
extern void loadList_ImageCollector(ImageCollector* myImageCollector, Asset* assetsList);
extern void unload_ImageCollector(ImageCollector* myImageCollector, const char name[]);
extern void unloadList_ImageCollector(ImageCollector* myImageCollector, Asset* assetsList);

extern Image* get_ImageCollector(ImageCollector* myImageCollector, const char name[]);

#endif //FREE_PROJECT_ENGINE_COLLECTORS_IMAGE_H
