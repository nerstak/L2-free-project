#ifndef FREE_PROJECT_TEST_CONDITION_H
#define FREE_PROJECT_TEST_CONDITION_H

#include "symbol.h"

typedef struct Condition {
    int keyLevel;
} Condition;

extern Condition* initTrue_Condition();
extern Condition* initSymbol_Condition(Symbol* mySymbol);
extern Condition* initCopy_Condition(Condition* other);
extern void clean_Condition(Condition** myCondition);

extern bool isEqual_Condition(Condition* myCondition, Condition* other);
extern void addSymbol_Condition(Condition* myCondition, Symbol* mySymbol);
extern void addCondition_Condition(Condition* myCondition, Condition* other);
extern Condition* initAndSymbol_Condition(Condition* myCondition, Symbol* mySymbol);
extern Condition* initAndCondition_Condition(Condition* myCondition, Condition* other);
extern bool impliesCondition_Condition(Condition* myCondition, Condition* other);
extern bool impliesSymbol_Condition(Condition* myCondition, Symbol* symbol);
extern Symbol* singleSymbolDifference_Condition(Condition* myCondition, Condition* other);
extern void printf_Condition(Condition* myCondition);
extern int getKeyLevel_Condition(Condition* myCondition);


#endif //FREE_PROJECT_TEST_CONDITION_H
