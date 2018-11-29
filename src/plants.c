#include <stdlib.h>
#include <string.h>

#include "plants.h"
#include "data.h"


static Plant* init_Plants(int x,int y);

extern field_t* initField(){
     field_t* field = malloc(sizeof(field_t));
     if(field == NULL){
         printf("Allocation of field_t failed.");
         exit(EXIT_FAILURE);
     }
     field->plantBotLeft = init_Plants(15,5);
     field->plantBotRight = init_Plants(17,5);
     field->plantTopLeft = init_Plants(15,2);
     field->plantTopRight = init_Plants(17,2);

     return field;
}



static Plant* init_Plants(int x,int y){
    Plant* temp = NULL;
    temp = malloc(sizeof(Plant));
    if(temp == NULL){
        printf("Allocation of Plant failed.");
        exit(EXIT_FAILURE);
    }
    temp->dayLeft = 0;
    temp->idVegetable = -1;
    temp->x = x;
    temp->y = y;
    return temp;
}

extern Plant* assignPlant(int n, field_t* field) {
    if(field == NULL) {
        return NULL;
    }
    switch(n) {
        case 0: {
            return field->plantTopLeft;
        }
        case 1: {
            return field->plantTopRight;
        }
        case 2: {
            return field->plantBotLeft;
        }
        case 3: {
            return field->plantBotRight;
        }
        default: {
            return NULL;
        }
    }
}
