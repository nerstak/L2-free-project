#ifndef FREE_PROJECT_ENGINE_GAME_DUNGEON_UTILS_DIRECTION_H
#define FREE_PROJECT_ENGINE_GAME_DUNGEON_UTILS_DIRECTION_H

/**
 * N:0 0 -1
 * E:1 1 0
 * S:2 0 1
 * W:3 -1 0
 */

/**
 * 4 Direction possible
 */

typedef struct Direction {
    int code;
    int x;
    int y;
} Direction;

/**
 * Create a Direction object with given "axises"
 * @param code the code corresponding to the direction (N, E, S, W)
 * @param x    the X axis
 * @param y    the Y axis
 * @return a Direction object
 */
extern Direction* init_Direction(int code, int x, int y);
/**
 * Clean a Direction object
 * @param myDirection a double pointer to a Direction object
 */
extern void clean_Direction(Direction** myDirection);

/**
 * Get a Direction object from a given code
 * @param code the code corresponding to the direction (N, E, S, W)
 * @return a Direction object
 */
extern Direction* fromCode_Direction(int code);
/**
 * Get the opposite Direction to a given one
 * @param myDirection the given position
 * @return a Direction object opposed to the given one
 */
extern Direction* opposite_Direction(Direction* myDirection);

#endif //FREE_PROJECT_ENGINE_GAME_DUNGEON_UTILS_DIRECTION_H
