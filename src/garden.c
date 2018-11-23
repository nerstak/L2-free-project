#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "data.h"
#include "engine/save.h"
#include "garden.h"

extern void doAction(Data* data){
    data->lobby->askAction = 0;
    switch (checkAction(data)){
    case(0) : break;
    case(1) :
        data->lobby->menuHouse = 1;
        data->lobby->askMove = 0;
        break;
    case(2) : break;
    case(3) : break;
    default : break;
    }


}

extern int checkAction(Data* data){
    if(data->lobby->layout->map[((data->Isaac->movement->pos->y)/64)+2][((data->Isaac->movement->pos->x)/64)].type=='M')
        return 1;
    if(data->lobby->layout->map[(data->Isaac->movement->pos->y)/64][(data->Isaac->movement->pos->x)/64].type=='S')
        return 2;
    if(data->lobby->layout->map[(data->Isaac->movement->pos->y)/64][(data->Isaac->movement->pos->x)/64].type=='P')
        return 3;
    return 0;
}

extern void processMenu1(Data* data){
    if(data->lobby->askAction == 0){
        if( data->lobby->askMove > 1)
            data->lobby->askMove = 1;
        if(data->lobby->askMove < 0)
            data->lobby->askMove = 0;
    }
    else if(data->lobby->askAction == 1){
        if(data->lobby->askMove == 0){
            write_Save(data);
            printf("%d day",data->Isaac->day);
        }
        else{
        }
        data->lobby->askAction = 0;
        data->lobby->menuHouse = 0;
    }
}

extern void counterOverWritting(Data* data){
    if(data->lobby->counterPressKey == 1 && data->lobby->askAction == 1){
        data->lobby->counterPressKey = 0;
        data->lobby->askAction = 0;
    }
}

