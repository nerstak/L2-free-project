#ifndef PLANTS_H_INCLUDED
#define PLANTS_H_INCLUDED

//0-Not 1-Tomato 2-Eggplant 3-Carotte
typedef struct Plant{
    int vegetable;
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

/**
 * Initialise a field_t Object
 * @return A pointer to a field_t Object
 */
extern field_t* initField();

#endif // PLANTS_H_INCLUDED
