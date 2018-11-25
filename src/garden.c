#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "data.h"
#include "engine/save.h"
#include "garden.h"
#include "plants.h"

static void test_plant(Data* data);

extern void doAction(Data* data){
    data->lobby->askAction = 0;
    switch (checkAction(data)){
    case(0) : break;
    case(1) :
        data->lobby->menuHouse = 1;
        data->lobby->askMove = 0;
        break;
    case(2) :
        data->lobby->menuHouse = 2;
        data->lobby->askMove = 0;
        break;
    case(3) : break;
    default : break;
    }


}

extern int checkAction(Data* data){
    if(data->lobby->layout->map[(int) ((data->Isaac->movement->pos->y)/64)+2][(int) ((data->Isaac->movement->pos->x)/64)].type == 'M'){
        return 1;
    }
    if(data->lobby->layout->map[((int) (data->Isaac->movement->pos->y)/64)+2][(int) (data->Isaac->movement->pos->x)/64].type == 'P'){
        return 2;
    }
    if(data->lobby->layout->map[(int) (data->Isaac->movement->pos->y)/64][(int) (data->Isaac->movement->pos->x)/64].type == 'S')
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

extern void processMenu2(Data* data){
        test_plant(data);
        processField(data);
}

static void test_plant(Data* data){
    if((int) (data->Isaac->movement->pos->x)/64 == 15 ){
        if( (int) (data->Isaac->movement->pos->y)/64 +2 == 5 ){
            data->lobby->actualPlant = data->field->plantBotLeft ;
           // printf("%d %d %d %d ",data->lobby->actualPlant->dayLeft,data->lobby->actualPlant->vegetable,data->lobby->actualPlant->x,data->lobby->actualPlant->y );
        }
        else if( (int) (data->Isaac->movement->pos->y)/64 +2 == 2 ){
            data->lobby->actualPlant = data->field->plantTopLeft ;
        }
    }
    else if((int) (data->Isaac->movement->pos->x)/64  == 17 ){
            if( (int) (data->Isaac->movement->pos->y)/64 +2 == 5){
                data->lobby->actualPlant = data->field->plantBotRight ;
            }
            else if( (int) (data->Isaac->movement->pos->y)/64 +2 == 2 ){
                data->lobby->actualPlant = data->field->plantTopRight ;
            }
    }
    else
        data->lobby->actualPlant = NULL;
}

extern void processField(Data* data){
    printf("%d %d %d %d ",data->lobby->actualPlant->dayLeft,data->lobby->actualPlant->vegetable,data->lobby->actualPlant->x,data->lobby->actualPlant->y );

    if( data->lobby->actualPlant->vegetable == 0){
        data->lobby->menuHouse = 21; // plant ?

    }
    else if(data->lobby->actualPlant->dayLeft == 0){
        data->lobby->menuHouse = 22; //go to dj?
    }
    else if(data->lobby->actualPlant->dayLeft != 0){
        data->lobby->menuHouse = 23;
    }

}

extern void menuSelectionDonjon(Data* data){
    if(data->lobby->askAction == 0){
        if( data->lobby->askMove > 1)
            data->lobby->askMove = 1;
        if(data->lobby->askMove < 0)
            data->lobby->askMove = 0;
    }
    else if(data->lobby->askAction == 1){
        if(data->lobby->askMove == 0){
            //go to donjon
        }
        else{
        }
            data->lobby->askAction = 0;
            data->lobby->menuHouse = 0;
    }

}

extern void menuSelectionPlanting(Data* data){
    if(data->lobby->askAction == 0){

            printf("%d",data->lobby->askMove);
            if( data->lobby->askMove > 3)
                data->lobby->askMove = 3;
            if(data->lobby->askMove < 0)
                data->lobby->askMove = 0;
    }
    else if(data->lobby->askAction == 1){
        if(data->lobby->askMove == 0){
            data->lobby->actualPlant->dayLeft = 3; //BIG PROBLEME WITH SATURATION
            data->lobby->actualPlant->vegetable = 1;

        }
        else if(data->lobby->askMove == 1){
            data->lobby->actualPlant->dayLeft = 3;
            data->lobby->actualPlant->vegetable = 2;
        }
        else if(data->lobby->askMove == 2){
            data->lobby->actualPlant->dayLeft = 3;
            data->lobby->actualPlant->vegetable = 3 ;
        }
        else if(data->lobby->askMove == 3){

        }
        data->lobby->actualPlant->dayLeft = NULL;
        data->lobby->menuHouse = 0;
        printf("That's a test \n");
    }
}

