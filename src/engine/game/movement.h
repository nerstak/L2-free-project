#ifndef FREE_PROJECT_ENGINE_GAME_MOVEMENT_H
#define FREE_PROJECT_ENGINE_GAME_MOVEMENT_H

typedef struct Coordinate {
    float x;
    float y;
} Coordinate;

typedef struct MovementValues {
    Coordinate* position;
    Coordinate* velocity;
    int animationStep;
    int direction;
    SDL_Rect* spriteBox;
    SDL_Rect* hitBox;
    Timer* timeSince;
    int stepChannel;
} MovementValues;

struct Data;
struct Tiles;

/**
 * Init a Coordinate Object
 * @return a pointer to a Coordinate Object
 */
extern Coordinate* init_Coordinate();
/**
 * Free a Coordinate Object
 * @param p a double pointer to a Coordinate Object
 */
extern void clean_Coordinate(Coordinate** p);

/**
 * Init a MovementValues Object
 * @return a pointer to a MovementValues Object
 */
extern MovementValues* init_Movement();
/**
 * Free a MovementValues Object
 * @param p a double pointer to a MovementValues Object
 */
extern void clean_Movement(MovementValues** p);

/**
 * Move the Player according to its environment
 * @param data a pointer to a Data Object
 * @param map a double pointer to a Tiles Object
 */
extern void movePlayer_Movement(struct Data* data, struct Tiles** map);
/**
 * Process the velocity of the Player
 * @param v a pointer to a float of the velocity on an axis
 * @param t an int corresponding to the time of displacement
 * @param max a float of the absolute maximum velocity
 * @param factor a float of the m
 */
extern void processVelocity_Movement(float* v, int t, float max, float factor);
/**
 * Set the velocity to 0
 * @param move a pointer to a MovementValues Object
 */
extern void stopVelocity_Movement(MovementValues* move);
/**
 * Adjust velocity according to obstacles
 * @param data a pointer to a Data Object
 * @param t an int representing the duration of displacement
 * @param speedStat float of the Speed Stat of the Player
 * @param map a double pointer to a Tiles Object
 * @param dampen int of how much the player is slow down if needed
 */
extern void checkObstacle_Movement(struct Data* data, int t, float speedStat, struct Tiles** map,float* dampen);
/**
 * Process the animation
 * @param move a pointer to a MovementValues Object
 * @param t an int representing the duration of displacement
 * @param speedStat float of the Speed Stat of the Player
 */
extern void processAnimation_Movement(MovementValues* move, int t, float speedStat);
/**
 * Select the correct frame to display
 * @param move a pointer to a MovementValues Object
 * @param box a pointer to a SDl_Rect Object for the Player
 */
extern void spriteSelection_Movement(MovementValues* move, SDL_Rect* box);
/**
 * Block the movement of the player if he is out of band
 * @param data a pointer to a Data Object
 * @param w int of the width of the Map
 * @param h int of the height of the Map
 * @param deltaW int of the shift width
 * @param deltaH int of the shift height
 */
extern void checkBound_Movement(struct Data* data, int w, int h, int deltaW, int deltaH);
/**
 * Set the hitbox of the Player
 * @param move a pointer to a MovementValues Object
 */
extern void setPlayerHitBox_Movement(MovementValues* move);

/**
 * Type of the of tile
 * @param tile char of the tile
 * @param result pointer of char receiving
 */
extern void Tiletype(char tile, char* result);

/**
 * Very rudimentary displacement of the Player by the Computer
 * @param data a pointer to a Data Object
 * @param Vchange float of the displacement
 * @param x_toGO int of the X-Position to go
 * @param y_toGO int of the Y-Position to go
 * @return int attesting or not the presence of the Player near the Coordinates
 */
extern int automaticAskMovement(struct Data* data, float Vchange, int x_toGO, int y_toGO);

#endif // FREE_PROJECT_ENGINE_GAME_MOVEMENT_H
