#include <stdlib.h>
#include <string.h>

#include "plants.h"
#include "data.h"


static Plant * init_Plants(int x,int y);

extern void init_Field(Data * data){
     data->field = malloc(sizeof(field_t));
     if( data->field == NULL){
         printf("data->field is NULL");
         exit(EXIT_FAILURE);
     }
     data->field->plantBotLeft = init_Plants(15,5);
     data->field->plantBotRight = init_Plants(17,5);
     data->field->plantTopLeft = init_Plants(15,2);
     data->field->plantTopRight = init_Plants(17,2);
}



static Plant * init_Plants(int x,int y){
    Plant * temp = NULL;
    temp = malloc(sizeof(Plant));
    if(temp == NULL){
        printf("probleme allocation plants");
        exit(EXIT_FAILURE);
    }
    temp->dayLeft = 0;
    temp->vegetable = 0;
    temp->x = x;
    temp->y = y;
    return temp;
}
