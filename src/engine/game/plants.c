#include <stdlib.h>
#include <string.h>

#include "plants.h"
#include "../collectors/image.h"
#include "../data.h"


static Plant* init_Plants(int x,int y);
static void freePlant(Plant** Plant);

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

extern void freeField(field_t** field) {
    if(field) {
        if(*field) {
            freePlant(&((*field)->plantBotRight));
            freePlant(&((*field)->plantBotLeft));
            freePlant(&((*field)->plantTopRight));
            freePlant(&((*field)->plantTopLeft));

            free(*field);
            *field = NULL;
        }
    }
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

static void freePlant(Plant** Plant) {
    if(Plant) {
        if(*Plant) {
            free(*Plant);
            *Plant = NULL;
        }
    }
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

extern void plantsBlit(SDL_Surface* lobbySurface, Data* data, ImageCollector* myImageCollector, char type) {
    SDL_Surface* plant = NULL;
    SDL_Rect plantPos;
    SDL_Rect plantSize;
    Plant* currentPlant = NULL;

    if(type == 'b') {
        plant = get_ImageCollector(myImageCollector,"lobby/plants_blur")->surface;
    } else {
        plant = get_ImageCollector(myImageCollector,"lobby/plants")->surface;
    }


    plantSize.h = 64;
    plantSize.w = 64;

    for(int i = 0; i < 4; i++) {
        currentPlant = assignPlant(i, data->field);
        if(currentPlant) {
            if(currentPlant->idVegetable != -1) {
                plantSize.x = currentPlant->idVegetable * 64;
                plantSize.y = (currentPlant->dayLeft)==0?64:0;

                plantPos.x = currentPlant->x * 64;
                plantPos.y = currentPlant->y * 64;

                SDL_BlitSurface(plant, &plantSize, lobbySurface, &plantPos);
            }
        }
    }
}
