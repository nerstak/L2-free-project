#ifndef FREE_PROJECT_UTILS_COORD_H
#define FREE_PROJECT_UTILS_COORD_H

#include <stdbool.h>

#include "direction.h"

typedef struct Coord {
    int x;
    int y;
} Coord;

extern Coord* init_Coord(int x, int y);
extern void clean_Coord(Coord** myCoord);

extern Coord* nextInDirection_Coord(Coord* myCoord, Direction* myDirection);
extern Coord* add_Coord(Coord* myCoord, int dx, int dy);
extern Coord* substract_Coord(Coord* myCoord, int dx, int dy);

extern bool isEqual_Coord(Coord* myCord, Coord* other);
extern int compareTo_Coord(Coord* myCoord, Coord* other);
extern bool isAdjacent_Coord(Coord* myCoord, Coord* other);
extern Direction* getDirectionTo_Coord(Coord* myCoord, Coord* other);
extern double distance_Coord(Coord* myCoord, Coord* other);
extern void printf_Coord(Coord* myCoord);

#endif //FREE_PROJECT_UTILS_COORD_H
