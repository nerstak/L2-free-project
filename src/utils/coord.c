#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "coord.h"

extern Coord* init_Coord(int x, int y) {
    // Initialization of a Coord pointer
    Coord* myCoord = NULL;
    myCoord = malloc(1 * sizeof(Coord));

    // If we failed to allocate, exit the program
    if (myCoord == NULL) {
        printf("An error occured while initializing a Coord object");
        exit(EXIT_FAILURE);
    }

    myCoord->x = x;
    myCoord->y = y;

    return myCoord;
}

extern void clean_Coord(Coord** myCoord) {
    if ((*myCoord) != NULL) {
        // First we free the memory
        free(*(myCoord));
        // We set the pointer to NULL by security
        *(myCoord) = NULL;
    }
}

extern Coord* nextInDirection_Coord(Coord* myCoord, Direction* myDirection) {
    // Using the direction, we can compute the coordinate
    return add_Coord(myCoord, myDirection->x, myDirection->y);
}

extern Coord* add_Coord(Coord* myCoord, int dx, int dy) {
    // Small computation of values
    return init_Coord(myCoord->x + dx, myCoord->y + dy);
}

extern Coord* substract_Coord(Coord* myCoord, int dx, int dy) {
    // Small computation of values
    return init_Coord(myCoord->x - dx, myCoord->y - dy);
}

extern bool isEqual_Coord(Coord* myCord, Coord* other) {
    return myCord->x == other->x && myCord->y == other->y;
}

extern int compareTo_Coord(Coord* myCoord, Coord* other) {
    // We compute the X difference
    int d = myCoord->x - other->x;

    // If the difference in height is equal to 0, we compute the Y difference
    if (d == 0) {
        d = myCoord->y - other->y;
    }

    return d;
}

extern bool isAdjacent_Coord(Coord* myCoord, Coord* other) {
    // We compute the distances
    int dx = abs(myCoord->x - other->x);
    int dy = abs(myCoord->y - other->y);

    // We return a boolean
    return (dx == 1 && dy == 0) || (dx == 0 && dy == 1);
}

extern Direction* getDirectionTo_Coord(Coord* myCoord, Coord* other) {
    // We compute the distances
    int dx = abs(myCoord->x - other->x);
    int dy = abs(myCoord->y - other->y);

    if (dx < 0) {
        return init_Direction(1, 1, 0);
    }

    if (dx > 0) {
        return init_Direction(3, -1, 0);
    }

    if (dy < 0) {
        return init_Direction(2, 0, 1);
    }

    if (dy > 0) {
        return init_Direction(0, 0, -1);
    }

    return NULL;
}

extern double distance_Coord(Coord* myCoord, Coord* other) {
    int dx = myCoord->x - other->x;
    int dy = myCoord->y - other->y;

    return sqrt(dx * dx + dy * dy);
}

extern void printf_Coord(Coord* myCoord) {
    printf("x: %d - y: %d\n", myCoord->x, myCoord->y);
}