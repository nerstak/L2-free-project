#ifndef MOVEMENT_H_INCLUDED
#define MOVEMENT_H_INCLUDED


extern void MovePlayer(Data* data);

extern void ProcessVelocity(float* v,int t);

extern void StopVelocity(MovementValues * move);

extern void CheckObstacle(Data* data,int t,float speedstat);

extern void ProcessAnimation(MovementValues * move,int t,float speedstat);

extern void SpriteSelection(MovementValues * move, SDL_Rect * box);

#endif // MOVEMENT_H_INCLUDED
