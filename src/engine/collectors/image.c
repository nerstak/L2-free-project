#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include "image.h"
#include "../asset.h"
#include "sound.h"

static void add_Image(ImageCollector* myImageCollector, Image* myImage);
static void remove_Image(ImageCollector* myImageCollector, Image* myImage);

static Image* isLoaded_ImageCollector(ImageCollector* myImageCollector, const char name[]);

static void add_Image(ImageCollector* myImageCollector, Image* myImage) {
    // Is our list of images empty ?
    if (myImageCollector->images == NULL) {
        // We write directly to the pointer
        myImageCollector->images = myImage;
        myImageCollector->size += 1;
    } else {
        // We find the last element of the list
        Image* temp = NULL;
        temp = myImageCollector->images;

        while (temp->next != NULL) {
            temp = temp->next;
        }

        // We add our element
        temp->next = myImage;
        myImageCollector->size += 1;
    }
}

static void remove_Image(ImageCollector* myImageCollector, Image* myImage) {
    Image* temp = myImageCollector->images;
    Image* previous = myImageCollector->images;

    // Is the element we want to remove the first one ?
    if (strcmp(temp->name, myImage->name) == 0) {
        // We rewrite the head of our list
        myImageCollector->images = temp->next;
        myImageCollector->size -= 1;

        // Don't forget to free the surface and the memory :D
        SDL_FreeSurface(temp->surface);
        free(temp);
    } else {
        // We find the position of the element we want to remove
        while (temp != NULL && strcmp(temp->name, myImage->name) != 0) {
            previous = temp;
            temp = temp->next;
        }

        if (temp == NULL) {
            return;
        }

        // Relink our list
        previous->next = temp->next;

        // Don't forget to free the surface and the memory :D
        SDL_FreeSurface(temp->surface);
        free(temp);

        myImageCollector->size -= 1;
    }
}

extern ImageCollector* init_ImageCollector() {
    // Initialization of a ImageCollector pointer
    ImageCollector* myImageCollector = NULL;
    myImageCollector = malloc(1 * sizeof(ImageCollector));

    // If we failed to allocate, exit the program
    if (myImageCollector == NULL) {
        printf("An error occured while initializing a ImageCollector object\n");
        exit(EXIT_FAILURE);
    }

    // Default value of our instance
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
    // Is it already loaded ?
    if (isLoaded_ImageCollector(myImageCollector, name) != NULL) {
        printf("An attempt to load a cached texture was blocked (%s)\n", name);

        return;
    }

    // We optimize the texture
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;

    loadedImage = IMG_Load(path);

    if (loadedImage == NULL) {
        printf("%s", SDL_GetError());
        printf("An error occured while loading a Image object\n");
        exit(EXIT_FAILURE);
    }

    optimizedImage = SDL_DisplayFormatAlpha(loadedImage);

    if (optimizedImage == NULL) {
        printf("An error occured while optimizing a Image object\n");
        exit(EXIT_FAILURE);
    }

    // Therefore we free the unoptimized texture
    SDL_FreeSurface(loadedImage);

    // Adding the texture to our ImageCollector
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

    // We go through the list and call the existing function
    while (temp != NULL) {
        if (temp->type == 3) {
            load_ImageCollector(myImageCollector, temp->path, temp->name);
        }

        temp = temp->next;
    }
}

extern void unload_ImageCollector(ImageCollector* myImageCollector, const char name[]) {
    Image myImage;
    strcpy(myImage.name, name);

    // We remove one Image from our ImageCollector
    remove_Image(myImageCollector, &myImage);
}

extern void unloadList_ImageCollector(ImageCollector* myImageCollector, Asset* assetsList) {
    Asset* temp = NULL;

    temp = assetsList;

    // We go through the list and call the existing function
    while (temp != NULL) {
        if (temp->type == 3) {
            unload_ImageCollector(myImageCollector, temp->name);
        }

        temp = temp->next;
    }
}

extern Image* get_ImageCollector(ImageCollector* myImageCollector, const char name[]) {
    Image* temp = myImageCollector->images;

    // We retrieve the existing Image from our ImageCollector
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            return temp;
        }

        temp = temp->next;
    }

    // If we don't find it, we crash the program nicely to avoid a SegFault
    printf("Trying to load an unloaded Image (%s)\n", name);
    exit(EXIT_FAILURE);

    return NULL;
}

static Image* isLoaded_ImageCollector(ImageCollector* myImageCollector, const char name[]) {
    Image* temp = myImageCollector->images;

    // We retrieve the existing Image from our ImageCollector
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            return temp;
        }

        temp = temp->next;
    }

    // Or we return NULL
    return NULL;
}

