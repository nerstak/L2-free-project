#ifndef FREE_PROJECT_UTILS_COORD_H
#define FREE_PROJECT_UTILS_COORD_H

#include <stdbool.h>

#include "direction.h"

typedef struct Coord {
    int x;
    int y;
} Coord;

/**
 * Create a Coord object with given coordinates
 * @param x the X coordinate
 * @param y the Y coordinate
 * @return a Coord object
 */
extern Coord* init_Coord(int x, int y);
/**
 * Clean a Coord object
 * @param myCoord a double pointer to a Coord object
 */
extern void clean_Coord(Coord** myCoord);

/**
 * Get the next Coord in a given Direction
 * @param myCoord     the origin Coord
 * @param myDirection the given Direction
 * @return a Coord object according to the origin and direction
 */
extern Coord* nextInDirection_Coord(Coord* myCoord, Direction* myDirection);
/**
 * Get the Coord with the added value
 * @param myCoord the origin Coord
 * @param dx      the X value to add
 * @param dy      the Y value to add
 * @return a Coord object according to the origin and values
 */
extern Coord* add_Coord(Coord* myCoord, int dx, int dy);
/**
 * Get the Coord with the substracted value
 * @param myCoord the origin Coord
 * @param dx      the X value to substract
 * @param dy      the Y value to substract
 * @return a Coord object according to the origin and values
 */
extern Coord* substract_Coord(Coord* myCoord, int dx, int dy);

/**
 * Verify if 2 Coord are equals
 * @param myCord the first Coord
 * @param other  the second Coord
 * @return a boolean according to the result
 */
extern bool isEqual_Coord(Coord* myCord, Coord* other);
/**
 * Comparator function of 2 Coord
 * @param myCoord the first Coord
 * @param other   the second Coord
 * @return a int according to the relative position
 */
extern int compareTo_Coord(Coord* myCoord, Coord* other);
/**
 * Verify if 2 Coord are adjacent
 * @param myCoord the first Coord
 * @param other   the second Coord
 * @return a boolean according to the result
 */
extern bool isAdjacent_Coord(Coord* myCoord, Coord* other);
/**
 * Get the direction toward the given coord
 * @param myCoord the first Coord
 * @param other   the second Coord
 * @return a Direction toward the second Coord
 */
extern Direction* getDirectionTo_Coord(Coord* myCoord, Coord* other);
/**
 * Get the distance between two Coord using Pythagoras theorem
 * @param myCoord the first Coord
 * @param other   the second Coord
 * @return a double which is the distance between the 2 Coord
 */
extern double distance_Coord(Coord* myCoord, Coord* other);
/**
 * Print a given Coord (test purpose)
 * @param myCoord the Coord to display
 */
extern void printf_Coord(Coord* myCoord);

#endif //FREE_PROJECT_UTILS_COORD_H
