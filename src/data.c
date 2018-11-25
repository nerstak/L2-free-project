#include <stdlib.h>
#include <stdio.h>

#include "data.h"

static void clean_mainMenu_Data(mainMenu_t** mainMenu);
static void clean_inventory_Data(inventory_t** inventory);
static void clean_shop_Data(shop_t** shop);

extern Data* init_Data() {
    // Initialization of a SceneCollector pointer
    Data* myData = NULL;
    myData = malloc(1 * sizeof(Data));

    // If we failed to allocate, exit the program
    if (myData == NULL) {
        printf("An error occured while initializing a Data object\n");
        exit(EXIT_FAILURE);
    }

    // Default value of our instance
    myData->inventory = NULL;
    myData->lobby = NULL;
    myData->mainMenu = NULL;
    myData->shop = NULL;

    //Loading of the reference
    myData->referenceItems = loadReferenceItems();

    //Loading player
    myData->Isaac = initPlayer();

    myData->stop = 1;

    return myData;
}

extern void clean_Data(Data** myData) {
    if ((*myData) == NULL) return;

    // First we clean the properties of our instance
    if ((*myData)->mainMenu != NULL) {
        clean_mainMenu_Data(&((*myData)->mainMenu));
    }
    if((*myData)->inventory != NULL) {
        clean_inventory_Data(&((*myData)->inventory));
    }
    if((*myData)->shop != NULL) {
        clean_shop_Data(&((*myData)->shop));
    }


    freeReference(&((*myData)->referenceItems));
    freePlayer(&((*myData)->Isaac));

    // We free this SceneCollector
    free(*myData);
    (*myData) = NULL;
}

static void clean_mainMenu_Data(mainMenu_t** mainMenu) {
    free(*mainMenu);
    (*mainMenu) = NULL;
}

static void clean_inventory_Data(inventory_t** inventory) {
    clean_Timer(&((*inventory)->timerMessage));
    (*inventory)->selected = NULL;
    free(*inventory);
    (*inventory) = NULL;
}

static void clean_shop_Data(shop_t** shop) {
    freeAll_SlotInventory(&((*shop)->shop_inv));
    (*shop)->selected = NULL;
    free(*shop);
    (*shop) = NULL;
}

