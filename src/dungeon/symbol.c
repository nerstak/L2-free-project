#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "symbol.h"

extern Symbol* init_Symbol(int value) {
    // Initialization of a Coord pointer
    Symbol* mySymbol = NULL;
    mySymbol = malloc(1 * sizeof(Symbol));

    // If we failed to allocate, exit the program
    if (mySymbol == NULL) {
        printf("An error occured while initializing a Coord object");
        exit(EXIT_FAILURE);
    }

    mySymbol->value = value;

    if (value == START) {
        strcpy(mySymbol->name, "Start");
    } else if (value == GOAL) {
        strcpy(mySymbol->name, "Goal");
    } else if (value == BOSS) {
        strcpy(mySymbol->name, "Boss");
    } else if (value >= 0 && value < 26) {
        mySymbol->name[0] = (char)((int) 'A' + value);
        mySymbol->name[1] = '\0';
    } else {
        mySymbol->name[0] = (char) value;
        mySymbol->name[1] = '\0';
    }

    return mySymbol;
}

extern void clean_Symbol(Symbol** mySymbol) {
    if ((*mySymbol) != NULL) {
        // First we free the memory
        free(*(mySymbol));
        // We set the pointer to NULL by security
        *(mySymbol) = NULL;
    }
}

extern bool isEqual_Symbol(Symbol* mySymbol, Symbol* other) {
    return mySymbol->value == other->value;
}

extern int hashCode_Symbol(Symbol* mySymbol) {
    return mySymbol->value;
}

extern int getValue_Symbol(Symbol* mySymbol) {
    return mySymbol->value;
}

extern bool isStart_Symbol(Symbol* mySymbol) {
    return mySymbol->value == START;
}

extern bool isGoal_Symbol(Symbol* mySymbol) {
    return mySymbol->value == GOAL;
}

extern bool isBoss_Symbol(Symbol* mySymbol) {
    return mySymbol->value == BOSS;
}

extern void printf_Symbol(Symbol* mySymbol) {
    printf("%s\n", mySymbol->name);
}