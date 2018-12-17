#ifndef FREE_PROJECT_ENGINE_GAME_PLANTS_H
#define FREE_PROJECT_ENGINE_GAME_PLANTS_H

#include "../collectors/image.h"

typedef struct Plant{ // -1: empty; 0:Carrot; 1:Tomato; 2:Potatoes; 3: Corn; 4: Eggplants
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
    struct Plant* currentPlant;
}field_t;

/**
 * Initialise a field_t Object
 * @return A pointer to a field_t Object
 */
extern field_t* initField();

/**
 * Free a field_t Object
 * @param field A double pointer to a field_t Object
 */
extern void freeField(field_t** field);

/**
 * Return the plant according to an int
 * @param n int corresponding to the number of the plant
 * @param field Pointer to the field
 * @return Pointer of plant
 */
extern Plant* assignPlant(int n, field_t* field);

/**
 * Blit the field
 * @param lobbySurface a pointer to a SDL_Surface
 * @param data a pointer to a Data Object
 * @param myImageCollector a pointer to an ImageCollector Object
 * @param type char indicating if the field has to be blurred or not ('b': blur; anything else: not)
 */
extern void plantsBlit(SDL_Surface* lobbySurface, struct Data* data, ImageCollector* myImageCollector, char type);

/**
 * Clean a plant and the currentPlant
 * @param n int corresponding to the number of the plant
 * @param field Pointer to field
 */
extern void removePlant(int n, field_t* field);

/**
 * Assign a number to a set of coordinates
 * @param coordX int of X-axis
 * @param coordY int of Y-axis
 * @param data pointer to Data Object
 * @return a pointer to a Plant Object, or NULL if not found
 */
extern Plant* assignNumberPlant_Coord(int coordX, int coordY, struct Data* data, int* number);

#endif // FREE_PROJECT_ENGINE_GAME_PLANTS_H
