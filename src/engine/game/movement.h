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

extern Coordinate* init_Coordinate();
extern void clean_Coordinate(Coordinate** p);

extern MovementValues* init_Movement();
extern void clean_Movement(MovementValues** p);

extern void movePlayer_Movement(struct Data* data, struct Tiles** map);
extern void processVelocity_Movement(float* v, int t, float max, float factor);
extern void stopVelocity_Movement(MovementValues* move);
extern void checkObstacle_Movement(struct Data* data, int t, float speedStat, struct Tiles** map,float* dampen);
extern void processAnimation_Movement(MovementValues* move, int t, float speedStat);
extern void spriteSelection_Movement(MovementValues* move, SDL_Rect* box);
extern void checkBound_Movement(struct Data* data, int w, int h, int deltaW, int deltaH);
extern void setPlayerHitBox_Movement(MovementValues* move);

extern void Tiletype(char tile, char* result);

extern int automaticAskMovement(struct Data* data, float Vchange, int x_toGO, int y_toGO);

#endif // FREE_PROJECT_ENGINE_GAME_MOVEMENT_H
