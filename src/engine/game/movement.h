#ifndef FREE_PROJECT_ENGINE_GAME_MOVEMENT_H
#define FREE_PROJECT_ENGINE_GAME_MOVEMENT_H


extern void MovePlayer(Data* data, Tiles** map);

extern void ProcessVelocity(float* v,int t);

extern void StopVelocity(MovementValues * move);

extern void CheckObstacle(Data* data, int t, float speedstat, Tiles** map);

extern void ProcessAnimation(MovementValues * move,int t,float speedstat);

extern void SpriteSelection(MovementValues * move, SDL_Rect * box);

extern void checkBound(Data* data, int w, int h, int deltaW, int deltaH);

extern int automaticAskMovement(Data* data, float Vchange, int x_toGO, int y_toGO);

#endif // FREE_PROJECT_ENGINE_GAME_MOVEMENT_H
