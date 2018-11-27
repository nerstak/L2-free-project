#ifndef PLANTS_H_INCLUDED
#define PLANTS_H_INCLUDED

#include "data.h"

typedef struct Plant{
    int vegetable; //0-Not 1-Tomato 2-Eggplant 3-Carotte
    int x;
    int y;
    int dayLeft;

}Plant;

typedef struct field_t{
    struct Plant * plantTopRight;
    struct Plant * plantTopLeft;
    struct Plant * plantBotRight;
    struct Plant * plantBotLeft;
}field_t;

extern void init_Field(Data * data);

#endif // PLANTS_H_INCLUDED
