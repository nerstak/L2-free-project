#include "bounds.h"

#include <stdio.h>
#include <stdlib.h>

extern Bounds* init_Bounds(int x, int y, int right, int bottom) {
    // Initialization of a Bounds pointer
    Bounds* p = NULL;
    p = malloc(1 * sizeof(Bounds));

    // If we failed to allocate, exit the program
    if (p == NULL) {
        printf("An error occured while initializing a Bounds object");
        exit(EXIT_FAILURE);
    }

    p->left = x;
    p->top = y;
    p->right = right;
    p->bottom = bottom;

    return p;
}

extern void clean_Bounds(Bounds** p) {
    if ((*p) != NULL) {
        // First we free the memory
        free(*(p));
        // We set the pointer to NULL by security
        *(p) = NULL;
    }
}

extern int width_Bounds(Bounds* p) {
    return p->right - p->left + 1;
}

extern int height_Bounds(Bounds* p) {
    return p->bottom - p->top + 1;
}

extern void printf_Bounds(Bounds* p) {
    printf("Bounds(%d,%d,%d,%d)", p->top, p->right, p->bottom, p->left);
}

