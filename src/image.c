#include <string.h>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include "image.h"
#include "asset.h"

static void add_Image(ImageCollector* myImageCollector, Image* myImage) {
    if (myImageCollector->images == NULL) {
        myImageCollector->images = myImage;
        myImageCollector->size += 1;
    } else {
        Image* temp = NULL;
        temp = myImageCollector->images;

        while (temp->next != NULL) {
            temp = temp->next;
        }

        temp->next = myImage;
        myImageCollector->size += 1;
    }
}

static void remove_Image(ImageCollector* myImageCollector, Image* myImage) {
    Image* temp = myImageCollector->images;
    Image* previous = myImageCollector->images;

    if (strcmp(temp->name, myImage->name) == 0) {
        myImageCollector->images = temp->next;
        myImageCollector->size -= 1;

        SDL_FreeSurface(temp->surface);
        free(temp);
    } else {
        while (temp != NULL && strcmp(temp->name, myImage->name) != 0) {
            previous = temp;
            temp = temp->next;
        }

        if (temp == NULL) {
            return;
        }

        previous->next = temp->next;

        SDL_FreeSurface(temp->surface);
        free(temp);

        myImageCollector->size -= 1;
    }
}

extern ImageCollector* init_ImageCollector() {
    ImageCollector* myImageCollector = NULL;
    myImageCollector = malloc(1 * sizeof(ImageCollector));

    if (myImageCollector == NULL) {
        printf("An error occured while initializing a ImageCollector object\n");
        exit(EXIT_FAILURE);
    }

    myImageCollector->size = 0;
    myImageCollector->images = NULL;

    return myImageCollector;
}

extern void clean_ImageCollector(ImageCollector** myImageCollector) {
    // First we clean the images SLL
    Image* temp = (*myImageCollector)->images;
    Image* next = NULL;

    while (temp != NULL) {
        next = temp->next;

        SDL_FreeSurface(temp->surface);
        free(temp);

        temp = next;
    }

    // We free this ImageCollector
    free(*myImageCollector);
    (*myImageCollector) = NULL;
}

extern void load_ImageCollector(ImageCollector* myImageCollector, const char path[], const char name[]) {
    if (isLoaded_ImageCollector(myImageCollector, name) != NULL) {
        printf("An attempt to load a cached texture was blocked (%s)\n", name);

        return;
    }

    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;

    loadedImage = IMG_Load(path);

    if (loadedImage == NULL) {
        printf("%s", SDL_GetError());
        printf("An error occured while loading a Image object\n");
        exit(EXIT_FAILURE);
    }

    optimizedImage = SDL_DisplayFormat(loadedImage);

    if (optimizedImage == NULL) {
        printf("An error occured while optimizing a Image object\n");
        exit(EXIT_FAILURE);
    }

    SDL_FreeSurface(loadedImage);

    Image* myImage = NULL;
    myImage = malloc(1 * sizeof(Image));

    if (myImage == NULL) {
        printf("An error occured while allocating a Image object\n");
        exit(EXIT_FAILURE);
    }

    strcpy(myImage->name, name);
    myImage->surface = optimizedImage;
    myImage->next = NULL;

    add_Image(myImageCollector, myImage);
}

extern void loadList_ImageCollector(ImageCollector* myImageCollector, Asset* assetsList) {
    Asset* temp = NULL;

    temp = assetsList;

    while (temp != NULL) {
        load_ImageCollector(myImageCollector, temp->path, temp->name);
        temp = temp->next;
    }
}

extern void unload_ImageCollector(ImageCollector* myImageCollector, const char name[]) {
    Image myImage;
    strcpy(myImage.name, name);

    remove_Image(myImageCollector, &myImage);
}

extern void unloadList_ImageCollector(ImageCollector* myImageCollector, Asset* assetsList) {
    Asset* temp = NULL;

    temp = assetsList;

    while (temp != NULL) {
        unload_ImageCollector(myImageCollector, temp->name);
        temp = temp->next;
    }
}

extern Image* get_ImageCollector(ImageCollector* myImageCollector, const char name[]) {
    Image* temp = myImageCollector->images;

    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            return temp;
        }

        temp = temp->next;
    }

    printf("Trying to load an unloaded Image (%s)\n", name);
    exit(EXIT_FAILURE);

    return NULL;
}

extern Image* isLoaded_ImageCollector(ImageCollector* myImageCollector, const char name[]) {
    Image* temp = myImageCollector->images;

    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            return temp;
        }

        temp = temp->next;
    }

    return NULL;
}

