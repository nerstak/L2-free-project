#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "asset.h"
#include "collectors/sound.h"
#include "main.h"

extern Asset* getList_Asset(char path[]) {
    // We open our file
    FILE* file = NULL;
    file = fopen(path, "r");

    // If it failed we kill the game
    if (file == NULL) {
        printf("An attempt to load a file failed\n");

        exit(EXIT_FAILURE);
    }

    // We allocate the first element of our SSL of Asset
    Asset* assetsList = NULL;
    assetsList = malloc(1 * sizeof(Asset));

    if (assetsList == NULL) {
        printf("An error occured while allocating a Asset object\n");
    }

    assetsList->next = NULL;

    // Preparation of our buffer
    char line[520] = "";
    int amount = 0;

    Asset* temp = assetsList;

    // We read our file line by line
    while (fgets(line, 520, file) != NULL) {
        char* path;
        char* name;

        // We split our line in two
        path = strtok(line, " ");
        name = strtok(NULL, " ");

        // Removing the return symbol
        name[strcspn(name, "\r\n")] = 0;

        // First element of our list case
        if (amount > 0) {
            temp->next = malloc(1 * sizeof(Asset));
            temp = temp->next;
            temp->next = NULL;
        }

        // We copy the data
        strcpy(temp->path, path);
        strcpy(temp->name, name);

        if (strstr(temp->path, ".wav") != NULL || strstr(temp->path, ".mp3") != NULL) {
            if (strstr(temp->path, "resources/sfx") != NULL) {
                temp->type = SOUND;
            } else if (strstr(temp->path, "resources/musics") != NULL) {
                temp->type = MUSIC;
            } else {
                printf("Referencing an unknown folder containing an audio file (.wav or .mp3)");
                exit(EXIT_FAILURE);
            }
        } else {
            temp->type = 3; // Image
        }

        amount += 1;
    }

    // Properly close the file
    fclose(file);

    // Returning the list
    return assetsList;
}

extern void clean_Asset(Asset** assetList) {
    // Is the list empty ?
    if ((*assetList) != NULL) {
        // Is the next element empty ?
        if ((*assetList)->next != NULL) {
            clean_Asset(&((*assetList)->next));
        }

        // We clean the element and put its pointer to NULL
        free((*assetList));
        (*assetList) = NULL;
    }
}

extern void load_Asset(char path[], bool loadOrUnload, struct Engine* engine, struct Data* data) {
    Asset* assetsList = getList_Asset(path);

    if (loadOrUnload == true) {
        loadList_ImageCollector(engine->imageCollector, assetsList);
        loadList_SoundCollector(engine->soundCollector, assetsList);
    } else {
        unloadList_ImageCollector(engine->imageCollector, assetsList);
        unloadList_SoundCollector(engine->soundCollector, assetsList);
    }

    clean_Asset(&assetsList);
}
