#include <stdlib.h>
#include <stdio.h>

#include "direction.h"

extern Direction* init_Direction(int code, int x, int y) {
    // Initialization of a Direction pointer
    Direction* myDirection = NULL;
    myDirection = malloc(1 * sizeof(Direction));

    // If we failed to allocate, exit the program
    if (myDirection == NULL) {
        printf("An error occured while initializing a Direction object");
        exit(EXIT_FAILURE);
    }

    myDirection->code = code;
    myDirection->x = x;
    myDirection->y = y;

    return myDirection;
}

extern void clean_Direction(Direction** myDirection) {
    // First we free the memory
    free(*(myDirection));
    // We set the pointer to NULL by security
    *(myDirection) = NULL;
}

extern Direction* opposite_Direction(Direction* myDirection) {
    switch (myDirection->code) {
        case 0: return init_Direction(2, 0, 1);
        case 1: return init_Direction(3, -1, 0);
        case 2: return init_Direction(0, 0, -1);
        case 3: return init_Direction(1, 1, 0);
        default: return NULL;
    }
}

extern Direction* fromCode_Direction(int code) {
    switch (code) {
        case 0: return init_Direction(0, 0, -1);
        case 1: return init_Direction(1, 1, 0);
        case 2: return init_Direction(2, 0, 1);
        case 3: return init_Direction(3, -1, 0);
        default: return NULL;
    }
}
