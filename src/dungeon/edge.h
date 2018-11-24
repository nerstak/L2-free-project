#ifndef FREE_PROJECT_DUNGEONS_EDGE_H
#define FREE_PROJECT_DUNGEONS_EDGE_H

#include "symbol.h"

typedef struct Edge {
    Symbol* symbol;
} Edge;

/**
 * Create a Edge object with a given Symbol
 * @param symbol the Symbol
 * @return a Edge object
 */
extern Edge* init_Edge(Symbol* symbol);
/**
 * Create a Edge object with no Symbol
 * @return a Edge object
 */
extern Edge* initEmpty_Edge();
/**
 * Clean a Edge object
 * @param myEdge a double pointer to a Edge object
 */
extern void clean_Edge(Edge** myEdge);

/**
 * Verify that a Edge has a Symbol (non empty one)
 * @param myEdge the Edge
 * @return a boolean according to the result
 */
extern bool hasSymbol_Edge(Edge* myEdge);
/**
 * Get the Symbol of an Edge
 * @param myEdge the Edge
 * @return a Symbol object
 */
extern Symbol* getSymbol_Edge(Edge* myEdge);
/**
 * Set the Symbol of an Edge
 * @param myEdge   the Edge
 * @param mySymbol the Symbol
 */
extern void setSymbol_Edge(Edge* myEdge, Symbol* mySymbol);
/**
 * Verify that 2 Edge are equals
 * @param myEdge the first Edge
 * @param other  the second Edge
 * @return a boolean according to the result
 */
extern bool isEqual_Edge(Edge* myEdge, Edge* other);

#endif //FREE_PROJECT_DUNGEONS_EDGE_H
