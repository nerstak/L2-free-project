#ifndef FREE_PROJECT_TEST_EDGE_H
#define FREE_PROJECT_TEST_EDGE_H

#include "symbol.h"

typedef struct Edge {
    Symbol* symbol;
} Edge;

extern Edge* init_Edge(Symbol* symbol);
extern Edge* initEmpty_Edge();
extern void clean_Edge(Edge** myEdge);

extern bool hasSymbol_Edge(Edge* myEdge);
extern Symbol* getSymbol_Edge(Edge* myEdge);
extern void setSymbol_Edge(Edge* myEdge, Symbol* mySymbol);
extern bool isEqual_Edge(Edge* myEdge, Edge* other);

#endif //FREE_PROJECT_TEST_EDGE_H
