#ifndef FREE_PROJECT_DUNGEONS_SYMBOL_H
#define FREE_PROJECT_DUNGEONS_SYMBOL_H

#include <stdbool.h>

typedef struct Symbol {
    int value;
    char name[255];
} Symbol;

enum symbolType {START = -1, GOAL = -2, BOSS = -3, KEY = -4};

extern Symbol* init_Symbol(int value);
extern void clean_Symbol(Symbol** mySymbol);

// My cord ????

extern bool isEqual_Symbol(Symbol* mySymbol, Symbol* other);
extern int hashCode_Symbol(Symbol* mySymbol);
extern int getValue_Symbol(Symbol* mySymbol);
extern bool isStart_Symbol(Symbol* mySymbol);
extern bool isGoal_Symbol(Symbol* mySymbol);
extern bool isBoss_Symbol(Symbol* mySymbol);
extern bool isKey_Symbol(Symbol* mySymbol);
extern void printf_Symbol(Symbol* mySymbol);

#endif //FREE_PROJECT_DUNGEONS_SYMBOL_H
