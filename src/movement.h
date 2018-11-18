#ifndef MOVEMENT_H_INCLUDED
#define MOVEMENT_H_INCLUDED


extern void MovePlayer(Data* data);

extern void ProcessVelocity(int * v);

extern void CheckObstacle(Data* data);

extern void ProcessAnimation(MovementValues * move);

extern void SpriteSelection(MovementValues * move, SDL_Rect * box);

#endif // MOVEMENT_H_INCLUDED
