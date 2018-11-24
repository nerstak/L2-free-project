#ifndef FREE_PROJECT_DUNGEONS_CONDITION_H
#define FREE_PROJECT_DUNGEONS_CONDITION_H

#include "symbol.h"

typedef struct Condition {
    int keyLevel;
} Condition;

/**
 * Create a Condition which is always True (empty condition)
 * @return a Condition object
 */
extern Condition* initTrue_Condition();
/**
 * Create a Condition with a given Symbol
 * @param mySymbol the Symbol to use as the condition
 * @return a Condition object
 */
extern Condition* initSymbol_Condition(Symbol* mySymbol);
/**
 * Create a Condition with a given Condition (a copy)
 * @param other the Condition to copy
 * @return a Condition object
 */
extern Condition* initCopy_Condition(Condition* other);
/**
 * Clean a Condition object
 * @param myCondition a double pointer to a Condition object
 */
extern void clean_Condition(Condition** myCondition);

/**
 * Verify if 2 Conditions are equals
 * @param myCondition the first Condition
 * @param other       the second Condition
 * @return a boolean according to the result
 */
extern bool isEqual_Condition(Condition* myCondition, Condition* other);
/**
 * Sum Condition with a Symbol
 * @param myCondition the Condition
 * @param mySymbol    the Symbol
 */
extern void addSymbol_Condition(Condition* myCondition, Symbol* mySymbol);
/**
 * Sum Condition with another one
 * @param myCondition the Condition
 * @param other       the Symbol
 */
extern void addCondition_Condition(Condition* myCondition, Condition* other);
/**
 * Create a AND Condition with a given Condition and Symbol
 * @param myCondition the Condition
 * @param mySymbol    the Symbol
 * @return a Condition object
 */
extern Condition* initAndSymbol_Condition(Condition* myCondition, Symbol* mySymbol);
/**
 * Create a AND Condition with two given Conditions
 * @param myCondition the Condition
 * @param other       the Condition
 * @return a Condition object
 */
extern Condition* initAndCondition_Condition(Condition* myCondition, Condition* other);
/**
 * Verify that the first Condition imply the second Condition
 * @param myCondition the first Condition
 * @param other       the second Condition
 * @return a boolean according to the result
 */
extern bool impliesCondition_Condition(Condition* myCondition, Condition* other);
/**
 * Verify that the first Condition imply the Symbol
 * @param myCondition the Condition
 * @param symbol      the Symbol
 * @return a boolean according to the result
 */
extern bool impliesSymbol_Condition(Condition* myCondition, Symbol* symbol);
/**
 * Create a Symbol object with the difference between two given Condition
 * @param myCondition the first Condition
 * @param other       the second Condition
 * @return a Symbol object
 */
extern Symbol* singleSymbolDifference_Condition(Condition* myCondition, Condition* other);
/**
 * Print a given Condition (test purpose)
 * @param myCondition the Condition to display
 */
extern void printf_Condition(Condition* myCondition);
/**
 * Get the keylevel of a Condition
 * @param myCondition the Condition
 * @return a integer corresponding to the keylevel of the Condition
 */
extern int getKeyLevel_Condition(Condition* myCondition);


#endif //FREE_PROJECT_DUNGEONS_CONDITION_H
