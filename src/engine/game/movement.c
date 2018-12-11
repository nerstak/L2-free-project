#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "../data.h"
#include "movement.h"
#include "combat.h"

extern Coordinate* init_Coordinate() {
    Coordinate* result = NULL;
    result = malloc(1 * sizeof(Coordinate));

    if (result == NULL) {
        exit(EXIT_FAILURE);
    }

    result->x = 0;
    result->y = 0;

    return result;
}

extern void clean_Coordinate(Coordinate** p) {
    if ((*p) != NULL) {
        free((*p));
        (*p) = NULL;
    }
}

extern MovementValues* init_Movement() {
    MovementValues* result = NULL;
    result = malloc(1 * sizeof(MovementValues));

    if (result == NULL) {
        exit(EXIT_FAILURE);
    }

    result->position = init_Coordinate();
    result->velocity = init_Coordinate();

    result->spriteBox = NULL;
    result->hitBox = NULL;

    result->spriteBox = malloc(1 * sizeof(SDL_Rect));
    result->hitBox = malloc(1 * sizeof(SDL_Rect));

    if (result->spriteBox == NULL || result->hitBox == NULL) {
        exit(EXIT_FAILURE);
    }

    result->timeSince = init_Timer();

    return result;
}

extern void clean_Movement(MovementValues** p) {
    if ((*p) != NULL) {
        clean_Coordinate(&((*p)->position));
        clean_Coordinate(&((*p)->velocity));

        free((*p)->spriteBox);
        free((*p)->hitBox);
        clean_Timer(&((*p)->timeSince));

        free((*p));
        (*p) = NULL;
    }
}

extern void movePlayer_Movement(Data* data, Tiles** map) {
    // Timer to get the time since the last frame of movement
    int timeChange = lap_Timer(data->Isaac->movement->timeSince);
    if(timeChange > 300) {
        timeChange = 0;
    }

    // Dampens and caps velocity
    processVelocity_Movement(&(data->Isaac->movement->velocity->x), timeChange, 12, 1);
    processVelocity_Movement(&(data->Isaac->movement->velocity->y), timeChange, 12, 1);

    float dampen=1;


    // Checks for obstacles on the map and adjusts velocity accordingly
    checkObstacle_Movement(data, timeChange, data->Isaac->stats->current->speed, map,&dampen);


    if(data->Isaac->combat->animationStep != 0) {
        dampen*=0.3;
    }

    //actually changes the character's movement according to the velocity we done got
    data->Isaac->movement->position->x += (data->Isaac->movement->velocity->x) * timeChange * 0.03 * data->Isaac->stats->current->speed * dampen;
    // timeChange*0.03 is equal to 0.5 at 60fps which, since max V is 12,means it moves 6 pixels a frame at 60 fps
    data->Isaac->movement->position->y += (data->Isaac->movement->velocity->y) * timeChange * 0.03 * data->Isaac->stats->current->speed * dampen;

    setPlayerHitBox_Movement(data->Isaac->movement);

    // takes care of the character's animation
    processAnimation_Movement(data->Isaac->movement, timeChange, data->Isaac->stats->current->speed);

    //selects the appropriate section of the spriteSheet to display
    spriteSelection_Movement(data->Isaac->movement, data->Isaac->movement->spriteBox);

    cap_Timer(data->Isaac->invulnerabilityTimer, 1000);
}

extern void processVelocity_Movement(float* v, int t, float max, float factor) {
    // Gradually slows down the player so he stops when not pressing the button
    if((*v) > 0) {
        // This is equal to 1 at 60 fps. This allows the acceleration to be equal to the deceleration
        (*v) -= ((t * 0.06) * factor);

        if((*v) < 0) {
            (*v) = 0;
        }
    } else if((*v) < 0) {
        (*v) += ((t * 0.06) * factor);

        if((*v) > 0) {
            (*v) = 0;
        }
    }

    // Caps velocity
    if((*v) > max) {
        (*v) = max;
    } else if((*v) < (-max)) {
        (*v) = (-max);
    }
}

extern void stopVelocity_Movement(MovementValues* move) {
    move->velocity->x=0;
    move->velocity->y=0;
    lap_Timer(move->timeSince);
}

extern void Tiletype(char tile, char* result)
{
    if(tile=='W'){*result='W';}
    if(tile=='B'){*result='B';}
    if(tile=='H'){*result='H';}
    if(tile=='J' && *result=='X'){*result='J';}
}


extern void checkObstacle_Movement(Data* data, int t, float speedStat, Tiles** map,float* dampen) {
    // X and Y coordinates of the top left of the player
    float xPos = data->Isaac->movement->position->x;
    float yPos = data->Isaac->movement->position->y;

    // this is the total change in position due to velocity
    float  Vx = (data->Isaac->movement->velocity->x) * t * (float) 0.03 * speedStat;
    float  Vy = (data->Isaac->movement->velocity->y) * t * (float) 0.03 * speedStat;

    // these 4 are the top bottom left and right values for the walls of the hitBox
    int top = (int) ((yPos + 85) / 64);
    int bot = (int) ((yPos + 120) / 64);
    int left = (int) ((xPos + 10) / 64);
    int right = (int) ((xPos + 54) / 64);

    // these are the layout-relative-coordinates of each side of the hitBox after they have moved from velocity
    int rightHit = (Vx + xPos + 54) / 64;
    int leftHit = (Vx + xPos + 10) / 64;
    int topHit = (Vy + yPos + 85) / 64;
    int botHit = (Vy + yPos + 120) / 64;

    checkBound_Movement(data, 1280, 704, 0, 0);

    Vx = (data->Isaac->movement->velocity->x);
    Vy = (data->Isaac->movement->velocity->y);

    char destType= 'X';

    if(Vx != 0 || Vy != 0) {
        // If one of the player's four corners is inside a wall after moving on an axis, it cancels movement.

        Tiletype(map[top][leftHit].type,&destType);
        Tiletype(map[top][rightHit].type,&destType);
        Tiletype(map[bot][leftHit].type,&destType);
        Tiletype(map[bot][rightHit].type,&destType);

        if(destType != 'X') {
            if(destType=='J')
                *dampen = 0.5;
            else
                data->Isaac->movement->velocity->x = 0;
        }

        destType= 'X';

        Tiletype(map[topHit][left].type,&destType);
        Tiletype(map[botHit][left].type,&destType);
        Tiletype(map[topHit][right].type,&destType);
        Tiletype(map[botHit][right].type,&destType);

        if(destType != 'X') {
            if(destType=='J')
                *dampen = 0.5;
            else
                data->Isaac->movement->velocity->y = 0;
        }
    }

    Vx = (data->Isaac->movement->velocity->x);
    Vy = (data->Isaac->movement->velocity->y);

    destType= 'X';

    if(Vx != 0 && Vy != 0) {

        Tiletype(map[topHit][leftHit].type,&destType);
        Tiletype(map[topHit][rightHit].type,&destType);
        Tiletype(map[botHit][leftHit].type,&destType);
        Tiletype(map[botHit][rightHit].type,&destType);
        // If the player moves towards a corner at a perfect angle, there wont be anything to block movement in both cardinal directions and we should hence check diagonals.
        if(destType != 'X') {
            if(destType != 'X') {
                if(destType=='J') {
                    *dampen = 0.5;
                } else{
                    data->Isaac->movement->velocity->x = 0;
                    data->Isaac->movement->velocity->y = 0;
                }
            }

        }
    }
}

extern void processAnimation_Movement(MovementValues* move, int t, float speedStat)
{
    if(move->velocity->x || move->velocity->y) {
        int stepPos = (int) (move->animationStep + (10 * speedStat * t * (float) 0.06));
        // Bases how much you advance in the animation on time change
        move->animationStep = stepPos % 440;
    }
    else {
        // Resets animation when player stops moving
        move->animationStep = 0;
    }

    //the direction of the player is based on the direction with the most velocity
    if(move->velocity->y > 0 && move->velocity->y >= move->velocity->x && -move->velocity->y <= move->velocity->x) //DOWN 0
        move->direction=0;
    else if(move->velocity->y < 0 && move->velocity->y <= move->velocity->x && -move->velocity->y >= move->velocity->x) // up 1
        move->direction=1;
    else if(move->velocity->x > 0) //RIGHT 2
        move->direction=2;
    else if(move->velocity->x < 0) //LEFT 3
        move->direction=3;


}

extern void spriteSelection_Movement(MovementValues* move, SDL_Rect* box) {
    // 0 1 2 3 based on where we are in the animation times the width of a single sprite
    box->x = (Sint16) ((move->animationStep / 55) * 64);
    // 0 1 2 3 based on direction times the width of a single sprite
    box->y = (Sint16) (move->direction * 128);
    // box->h=128;
    // box->w=64;
}

extern void checkBound_Movement(Data* data, int w, int h, int deltaW, int deltaH) {
    float Vx = data->Isaac->movement->velocity->x;
    float Vy = data->Isaac->movement->velocity->y;
    float xPos = data->Isaac->movement->position->x;
    float yPos = data->Isaac->movement->position->y;

    if((xPos + Vx) < deltaW || (xPos + Vx) > (w - data->Isaac->movement->spriteBox->w + deltaW)) {
        data->Isaac->movement->velocity->x = 0;
    }
    if((yPos + Vy + data->Isaac->movement->spriteBox->h) < (deltaH) || (yPos + Vy) >(h - data->Isaac->movement->spriteBox->h + deltaH)) {
        data->Isaac->movement->velocity->y = 0;
    }
}

extern int automaticAskMovement(Data* data, float Vchange, int x_toGO, int y_toGO) {
    Coordinate* posPlayer = data->Isaac->movement->position;
    if(posPlayer->y > (y_toGO + 5) || posPlayer->y < (y_toGO - 5) || posPlayer->x > (x_toGO + 25) || posPlayer->x < (x_toGO - 25)) {
        if(posPlayer->x > (x_toGO + 25) || posPlayer->x < (x_toGO - 25)) {
            if(posPlayer->x > x_toGO) {
                data->Isaac->movement->velocity->x -= Vchange;
            }
            if(posPlayer->x < x_toGO) {
                data->Isaac->movement->velocity->x += Vchange;
            }
        }

        if(posPlayer->y > (y_toGO + 5) || posPlayer->y < (y_toGO - 5)) {
            if(posPlayer->y > y_toGO) {
                data->Isaac->movement->velocity->y -= Vchange;
            }
            if(posPlayer->y < y_toGO) {
                data->Isaac->movement->velocity->y += Vchange;
            }
        }

        return 0;
    } else {
        return 1;
    }
}

extern void setPlayerHitBox_Movement(MovementValues* move)
{
    move->hitBox->x = (Sint16) (move->position->x);
    move->hitBox->y = (Sint16) (move->position->y + 32);
}
