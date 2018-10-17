#include <stdlib.h>
#include <SDL/SDL_video.h>

#ifndef FREE_PROJECT_IMAGE_H
#define FREE_PROJECT_IMAGE_H

typedef struct Image {
    char name[255];
    SDL_Surface* surface;

    struct Image* next;
} Image;

typedef struct ImageCollector {
    size_t size;
    Image* images;
} ImageCollector;

void add_Image(ImageCollector* myImageCollector, Image* myImage);
void remove_Image(ImageCollector* myImageCollector, Image* myImage);

ImageCollector* init_ImageCollector();
void clean_ImageCollector(ImageCollector** myImageCollector);

void load_ImageCollector(ImageCollector* myImageCollector, const char path[], const char name[]);
void unload_ImageCollector(ImageCollector* myImageCollector, const char name[]);

Image* get_ImageCollector(ImageCollector *myImageCollector, const char name[]);
Image* isLoaded_ImageCollector(ImageCollector *myImageCollector, const char name[]);

#endif //FREE_PROJECT_IMAGE_H
