#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ttf.h"

static void add_Font(FontCollector* myFontCollector, Font* myFont);
static void remove_Font(FontCollector* myFontCollector, Font* myFont);

static Font* isLoaded_FontCollector(FontCollector* myFontCollector, const char name[]);

static void add_Font(FontCollector* myFontCollector, Font* myFont) {
    // Is our list of fonts empty ?
    if (myFontCollector->fonts == NULL) {
        myFontCollector->fonts = myFont;
        myFontCollector->size += 1;
    } else {
        // We find the last element of the list
        Font* temp = NULL;
        temp = myFontCollector->fonts;

        while (temp->next != NULL) {
            temp = temp->next;
        }

        // We add our element
        temp->next = myFont;
        myFontCollector->size += 1;
    }
}

static void remove_Font(FontCollector* myFontCollector, Font* myFont) {
    Font* temp = myFontCollector->fonts;
    Font* previous = myFontCollector->fonts;

    // Is the element we want to remove the first one ?
    if (strcmp(temp->name, myFont->name) == 0) {
        // We rewrite the head of our list
        myFontCollector->fonts = temp->next;
        myFontCollector->size -= 1;

        // Don't forget to free the TTF_Font and the memory :D
        TTF_CloseFont(temp->font);
        free(temp);
    } else {
        // We find the position of the element we want to remove
        while (temp != NULL && strcmp(temp->name, myFont->name) != 0) {
            previous = temp;
            temp = temp->next;
        }

        if (temp == NULL) {
            return;
        }

        // Relink our list
        previous->next = temp->next;

        // Don't forget to free the surface and the memory :D
        TTF_CloseFont(temp->font);
        free(temp);

        myFontCollector->size -= 1;
    }
}

extern FontCollector* init_FontCollector() {
    // Initialization of a FontCollector pointer
    FontCollector* myFontCollector = NULL;
    myFontCollector = malloc(1 * sizeof(FontCollector));

    // If we failed to allocate, exit the program
    if (myFontCollector == NULL) {
        printf("An error occured while initializing a FontCollector object\n");
        exit(EXIT_FAILURE);
    }

    // Default value of our instance
    myFontCollector->size = 0;
    myFontCollector->fonts = NULL;

    return myFontCollector;
}

extern void clean_FontCollector(FontCollector** myFontCollector) {
    // First we clean the fonts SLL
    Font* temp = (*myFontCollector)->fonts;
    Font* next = NULL;

    while (temp != NULL) {
        next = temp->next;

        TTF_CloseFont(temp->font);
        free(temp);

        temp = next;
    }

    // We free this FontCollector
    free(*myFontCollector);
    (*myFontCollector) = NULL;
}

extern void load_FontCollector(FontCollector* myFontCollector, const char path[], const int size, const char name[]) {
    // Is it already loaded ?
    if (isLoaded_FontCollector(myFontCollector, name) != NULL) {
        printf("An attempt to load a cached font was blocked (%s)\n", name);

        return;
    }

    // Adding the font to our FontCollector
    Font* myFont = NULL;
    myFont = malloc(1 * sizeof(Font));

    if (myFont == NULL) {
        printf("An error occured while allocating a Font object\n");
        exit(EXIT_FAILURE);
    }

    strcpy(myFont->name, name);
    myFont->font = TTF_OpenFont(path, size);
    myFont->next = NULL;

    add_Font(myFontCollector, myFont);
}

extern void unload_FontCollector(FontCollector* myFontCollector, const char name[]) {
    Font myFont;
    strcpy(myFont.name, name);

    // We remove one Font from our FontCollector
    remove_Font(myFontCollector, &myFont);
}

extern Font* get_FontCollector(FontCollector* myFontCollector, const char name[]) {
    Font* temp = myFontCollector->fonts;

    // We retrieve the existing Font from our FontCollector
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            return temp;
        }

        temp = temp->next;
    }

    // If we don't find it, we crash the program nicely to avoid a SegFault
    printf("Trying to load an unloaded Font (%s)\n", name);
    exit(EXIT_FAILURE);

    return NULL;
}

static Font* isLoaded_FontCollector(FontCollector* myFontCollector, const char name[]) {
    Font* temp = myFontCollector->fonts;

    // We retrieve the existing Font from our FontCollector
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            return temp;
        }

        temp = temp->next;
    }

    // Or we return NULL
    return NULL;
}


extern int getWidth_FontCollector(TTF_Font* font, const char str[]) {
    int w, h;

    TTF_SizeText(font, str, &w, &h);

    return w;
}

extern int getHeight_FontCollector(TTF_Font* font, const char str[]) {
    int w, h;

    TTF_SizeText(font, str, &w, &h);

    return h;
}