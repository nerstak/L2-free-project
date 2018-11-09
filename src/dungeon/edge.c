#include <stdlib.h>
#include <stdio.h>

#include "edge.h"

extern Edge* init_Edge(Symbol* symbol) {
    // Initialization of a Coord pointer
    Edge* myEdge = NULL;
    myEdge = malloc(1 * sizeof(Edge));

    // If we failed to allocate, exit the program
    if (myEdge == NULL) {
        printf("An error occured while initializing a Coord object");
        exit(EXIT_FAILURE);
    }

    myEdge->symbol = symbol;

    return myEdge;
}

extern Edge* initEmpty_Edge() {
    // Initialization of a Coord pointer
    Edge* myEdge = NULL;
    myEdge = malloc(1 * sizeof(Edge));

    // If we failed to allocate, exit the program
    if (myEdge == NULL) {
        printf("An error occured while initializing a Coord object");
        exit(EXIT_FAILURE);
    }

    myEdge->symbol = NULL;

    return myEdge;
}

extern void clean_Edge(Edge** myEdge) {
    // First we free the memory
    free(*(myEdge));
    // We set the pointer to NULL by security
    *(myEdge) = NULL;
}

extern bool hasSymbol_Edge(Edge* myEdge) {
    return myEdge->symbol != NULL;
}

extern Symbol* getSymbol_Edge(Edge* myEdge) {
    return myEdge->symbol;
}

extern void setSymbol_Edge(Edge* myEdge, Symbol* mySymbol) {
    myEdge->symbol = mySymbol;
}

extern bool isEqual_Edge(Edge* myEdge, Edge* other) {
    return myEdge->symbol == other->symbol || isEqual_Symbol(myEdge->symbol, other->symbol);
}