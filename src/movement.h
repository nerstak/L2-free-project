#ifndef MOVEMENT_H_INCLUDED
#define MOVEMENT_H_INCLUDED


extern void MovePlayer(Data* data);

extern void ProcessVelocity(float* v,int t);

extern void CheckObstacle(Data* data,int t);

extern void ProcessAnimation(MovementValues * move,int t);

extern void SpriteSelection(MovementValues * move, SDL_Rect * box);

#endif // MOVEMENT_H_INCLUDED
