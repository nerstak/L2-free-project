#ifndef FREE_PROJECT_LAYOUT_H
#define FREE_PROJECT_LAYOUT_H

typedef struct Tiles{
    char type;
}Tiles;


typedef struct Coords {
    int x;
    int y;
    char* type;
}Coords;

typedef struct Layout{
    char* name;
    int columns;
    int lines;
    char* setMobs;
    Coords* Spawnable;
    Tiles** map;
}Layout;

/**
 * Load the layout of a map
 * @param environment String of the environment
 * @param name String of the specific room (no need for lobby)
 * @return Pointer of Layout Object
 */
extern Layout* loadSingleLayout(char* environment, char* name);
/**
 * Free a Layout Object
 * @param room Double pointer of Layout Object
 */
extern void freeSingleLayout(Layout** room);

#endif //FREE_PROJECT_LAYOUT_H
