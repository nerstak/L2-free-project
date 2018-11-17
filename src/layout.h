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


extern Layout* loadSingleLayout(char* environment, char* name);
extern void freeSingleLayout(Layout** room);

#endif //FREE_PROJECT_LAYOUT_H
