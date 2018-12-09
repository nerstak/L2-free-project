#include <stdlib.h>
#include <stdio.h>

#include "data.h"

static void clean_mainMenu_Data(mainMenu_t** mainMenu);
static void clean_inventory_Data(inventory_t** inventory);
static void clean_shop_Data(shop_t** shop);
static void clean_field_Data(field_t** field);
static void clean_lobby_Data(lobby_t** lobby);
static void clean_options_Data(options_t** options);
static void clean_pauseMenu_Data(pauseMenu_t** pauseMenu);

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
    myData->field = NULL;
    myData->options = NULL;
    myData->pauseMenu = NULL;

    //Loading of the reference
    myData->referenceItems = NULL;

    //Loading player
    myData->Isaac = NULL;

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
    if((*myData)->field != NULL) {
        clean_field_Data(&((*myData)->field));
    }
    if((*myData)->lobby != NULL) {
        clean_lobby_Data(&((*myData)->lobby));
    }
    if((*myData)->options != NULL) {
        clean_options_Data(&(*myData)->options);
    }
    if((*myData)->pauseMenu != NULL) {
        clean_pauseMenu_Data(&(*myData)->pauseMenu);
    }


    if((*myData)->referenceItems != NULL) {
        freeReference(&((*myData)->referenceItems));
    }
    if((*myData)->Isaac != NULL) {
        free_Player(&((*myData)->Isaac));
    }

    free(*myData);
    (*myData) = NULL;
}

static void clean_mainMenu_Data(mainMenu_t** mainMenu) {
    free(*mainMenu);
    (*mainMenu) = NULL;
}

static void clean_inventory_Data(inventory_t** inventory) {
    if((*inventory)->timerMessage != NULL) {
        clean_Timer(&((*inventory)->timerMessage));
    }

    (*inventory)->selected = NULL;
    free(*inventory);
    (*inventory) = NULL;
}

static void clean_shop_Data(shop_t** shop) {
    if((*shop)->timerMessage != NULL) {
        clean_Timer(&((*shop)->timerMessage));
    }

    freeAll_SlotInventory(&((*shop)->shop_inv));
    (*shop)->selected = NULL;
    free(*shop);
    (*shop) = NULL;
}

static void clean_field_Data(field_t** field) {
    freeField(field);
}

static void clean_lobby_Data(lobby_t** lobby) {
    (*lobby)->actualPlant = NULL;

    if((*lobby)->timerMessage != NULL) {
        clean_Timer(&((*lobby)->timerMessage));
    }

    if((*lobby)->layout != NULL) {
        freeSingle_Layout(&((*lobby)->layout));
    }
}

static void clean_options_Data(options_t** options) {
    free(*options);
    (*options) = NULL;
}

static void clean_pauseMenu_Data(pauseMenu_t** pauseMenu) {
    free(*pauseMenu);
    (*pauseMenu) = NULL;
}