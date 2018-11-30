#ifndef FREE_PROJECT_LAYOUT_H
#define FREE_PROJECT_LAYOUT_H

#include "../player.h"

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

/**
 * Check if the player is within the radius of a specific tile
 * @param player Pointer of Object Player
 * @param layout Pointer of Object Layout
 * @param type Char corresponding to the type of the tile we are seeking
 * @param radius Int of the radius search
 * @param deltaW Int of the delta between the coordinates and the window on the X-axis
 * @param deltaH Int of the delta between the coordinates and the window on the Y-axis
 * @param tileX Pointer of int keeping the X-coordinate of the tile if found and pointer not to NULL
 * @param tileY Pointer of int keeping the Y-coordinate of the tile if found and pointer not to NULL
 * @return Int (0: tile not found; 1 tile found)
 */
extern int checkTilesPlayer(Player* player,
        Layout* layout,
        char type,
        int radius,
        int deltaW,
        int deltaH,
        int* tileX,
        int* tileY);

#endif //FREE_PROJECT_LAYOUT_H
