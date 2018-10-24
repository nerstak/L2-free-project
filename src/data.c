#include <stdlib.h>
#include <stdio.h>

#include "data.h"

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

    return myData;
}

extern void clean_Data(Data** myData) {
    // First we clean the properties of our instance

    // We free this SceneCollector
    free(*myData);
    (*myData) = NULL;
}

