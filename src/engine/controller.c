#include "stdlib.h"
#include "stdio.h"

#include "controller.h"

extern referenceKey* initKeys() {
    referenceKey* newKeys = NULL;
    newKeys = malloc(sizeof(referenceKey));
    if(newKeys == NULL) {
        printf("Error during the init of an referenceKey object.");
        exit(EXIT_FAILURE);
    }
    return newKeys;
}

extern void cleanKeys(referenceKey** p) {
    if ((*p) != NULL) {
        free((*p));
        (*p) = NULL;
    }
}