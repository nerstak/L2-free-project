#ifndef PLANTS_H_INCLUDED
#define PLANTS_H_INCLUDED

typedef struct Plant{ // 0: empty 1:Carrot 2:Tomato 3:Potatoes 4: Corn 5: Eggplants
    int idVegetable;
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

/**
 * Return the plant according to an int
 * @param n int corresponding to the number of the plant
 * @param field Pointer to the field
 * @return Pointer of plant
 */
extern Plant* assignPlant(int n, field_t* field);

#endif // PLANTS_H_INCLUDED
