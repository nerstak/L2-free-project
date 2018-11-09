#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "condition.h"

#include "../utils/math.h"

extern Condition* initTrue_Condition() {
    // Initialization of a Coord pointer
    Condition* myCondition = NULL;
    myCondition = malloc(1 * sizeof(Condition));

    // If we failed to allocate, exit the program
    if (myCondition == NULL) {
        printf("An error occured while initializing a Condition object");
        exit(EXIT_FAILURE);
    }

    myCondition->keyLevel = 0;

    return myCondition;
}

extern Condition* initSymbol_Condition(Symbol* mySymbol) {
    // Initialization of a Coord pointer
    Condition* myCondition = NULL;
    myCondition = malloc(1 * sizeof(Condition));

    // If we failed to allocate, exit the program
    if (myCondition == NULL) {
        printf("An error occured while initializing a Condition object");
        exit(EXIT_FAILURE);
    }

    myCondition->keyLevel = getValue_Symbol(mySymbol) + 1;

    return myCondition;
}

extern Condition* initCopy_Condition(Condition* other) {
    // Initialization of a Coord pointer
    Condition* myCondition = NULL;
    myCondition = malloc(1 * sizeof(Condition));

    // If we failed to allocate, exit the program
    if (myCondition == NULL) {
        printf("An error occured while initializing a Condition object");
        exit(EXIT_FAILURE);
    }

    myCondition->keyLevel = other->keyLevel;

    return myCondition;
}

extern void clean_Condition(Condition** myCondition) {
    // First we free the memory
    free(*(myCondition));
    // We set the pointer to NULL by security
    *(myCondition) = NULL;
}

extern bool isEqual_Condition(Condition* myCondition, Condition* other) {
    return myCondition->keyLevel == other->keyLevel;
}

extern void addSymbol_Condition(Condition* myCondition, Symbol* mySymbol) {
    myCondition->keyLevel = max(myCondition->keyLevel, getValue_Symbol(mySymbol) + 1);
}

extern void addCondition_Condition(Condition* myCondition, Condition* other) {
    myCondition->keyLevel = max(myCondition->keyLevel, other->keyLevel);
}

extern Condition* initAndSymbol_Condition(Condition* myCondition, Symbol* mySymbol) {
    Condition* temp = initCopy_Condition(myCondition);
    addSymbol_Condition(temp, mySymbol);

    return temp;
}

extern Condition* initAndCondition_Condition(Condition* myCondition, Condition* other) {
    if (other == NULL) {
        return myCondition;
    }

    Condition* temp = initCopy_Condition(myCondition);
    addCondition_Condition(temp, other);

    return temp;
}

extern bool impliesCondition_Condition(Condition* myCondition, Condition* other) {
    return myCondition->keyLevel >= other->keyLevel;
}

extern bool impliesSymbol_Condition(Condition* myCondition, Symbol* symbol) {
    Condition* temp = initSymbol_Condition(symbol);
    bool result = impliesCondition_Condition(myCondition, temp);
    clean_Condition(&temp);

    return result;
}

extern Symbol* singleSymbolDifference_Condition(Condition* myCondition, Condition* other) {
    if (isEqual_Condition(myCondition, other)) {
        return NULL;
    }

    return init_Symbol(max(myCondition->keyLevel, other->keyLevel) - 1);
}

extern void printf_Condition(Condition* myCondition) {
    if (myCondition->keyLevel != 0) {
        Symbol* temp = init_Symbol(myCondition->keyLevel - 1);
        printf_Symbol(temp);
        clean_Symbol(&temp);
    }
}

extern int getKeyLevel_Condition(Condition* myCondition) {
    return myCondition->keyLevel;
}