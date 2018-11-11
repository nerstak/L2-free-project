#ifndef FREE_PROJECT_DUNGEONS_BOUNDS_H
#define FREE_PROJECT_DUNGEONS_BOUNDS_H

typedef struct Bounds { // Clockwise order (HTML)
    int top;
    int right;
    int bottom;
    int left;
} Bounds;

/**
 * Create a Bounds object with given coordinates.
 * @param x      the X coordinate of the left side of the rectangle
 * @param y      the Y coordinate of the top side of the rectangle
 * @param right  the X coordinate of the right side of the rectangle
 * @param bottom the Y coordinate of the bottom side of the rectangle
 * @return a Bounds object
 */
extern Bounds* init_Bounds(int x, int y, int right, int bottom);
/**
 * Clean a Bounds object
 * @param p a double pointer to a Bounds object
 */
extern void clean_Bounds(Bounds** p);

/**
 * Gets the width of the rectangle
 * @param p a pointer to a Bounds object
 * @return width of the rectangle
 */
extern int width_Bounds(Bounds* p);
/**
 * Gets the height of the rectangle
 * @param p a pointer to a Bounds object
 * @return height of the rectangle
 */
extern int height_Bounds(Bounds* p);

/**
 * Print the bounds of the rectangle
 * @param p a pointer to a Bounds object
 */
extern void printf_Bounds(Bounds* p);

#endif //FREE_PROJECT_DUNGEONS_BOUNDS_H
