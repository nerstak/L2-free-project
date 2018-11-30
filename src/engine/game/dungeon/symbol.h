#ifndef FREE_PROJECT_ENGINE_GAME_DUNGEON_SYMBOL_H
#define FREE_PROJECT_ENGINE_GAME_DUNGEON_SYMBOL_H

#include <stdbool.h>

typedef struct Symbol {
    int value;
    char name[255];
} Symbol;


enum symbolType {START = -1, GOAL = -2, BOSS = -3};

/**
 * Create a Symbol object with a given value
 * @param value the value of the Symbol
 * @return a Symbol object
 */
extern Symbol* init_Symbol(int value);
/**
 * Clean a Symbol object
 * @param mySymbol a double pointer to a Symbol object
 */
extern void clean_Symbol(Symbol** mySymbol);

/**
 * Verify if 2 Symbol are equals or not
 * @param mySymbol the first Symbol object
 * @param other    the second Symbol object
 * @return a boolean according to the result
 */
extern bool isEqual_Symbol(Symbol* mySymbol, Symbol* other);
/**
 * Get the decimal value of a a given Symbol
 * @param mySymbol a Symbol object
 * @return a Symbol decimal value, an integer
 */
extern int hashCode_Symbol(Symbol* mySymbol);
/**
 * Get the decimal value of a a given Symbol
 * @param mySymbol a Symbol object
 * @return a Symbol decimal value, an integer
 */
extern int getValue_Symbol(Symbol* mySymbol);
/**
 * Verify if a Symbol is the Start Symbol
 * @param mySymbol a Symbol object
 * @return a boolean according to the result
 */
extern bool isStart_Symbol(Symbol* mySymbol);
/**
 * Verify if a Symbol is the Goal Symbol
 * @param mySymbol a Symbol object
 * @return a boolean according to the result
 */
extern bool isGoal_Symbol(Symbol* mySymbol);
/**
 * Verify if a Symbol is the Boss Symbol
 * @param mySymbol a Symbol object
 * @return a boolean according to the result
 */
extern bool isBoss_Symbol(Symbol* mySymbol);
/**
 * Print a given Symbol (test purpose)
 * @param mySymbol the Symbol to display
 */
extern void printf_Symbol(Symbol* mySymbol);

#endif //FREE_PROJECT_ENGINE_GAME_DUNGEON_SYMBOL_H
