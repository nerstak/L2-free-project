#include "main.h"

extern Engine* init_Engine() {
    // Initialization of a Engine pointer
    Engine* p = NULL;
    p = malloc(1 * sizeof(Engine));

    // If we failed to allocate, exit the program
    if (p == NULL) {
        printf("An error occured while initializing a Engine object\n");
        exit(EXIT_FAILURE);
    }

    // Default value of our instance
    p->imageCollector = NULL;
    p->fontCollector = NULL;
    p->sceneCollector = NULL;

    return p;
}

extern void clean_Engine(Engine** p) {
    if ((*p) == NULL) return;

    // We free this Engine
    free(*p);
    (*p) = NULL;
}
