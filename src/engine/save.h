#ifndef FREE_PROJECT_ENGINE_SAVE_H
#define FREE_PROJECT_ENGINE_SAVE_H

#include "../data.h"

/**
 * Initialise the values of the Game
 * @param saveName String of the save we want to open (extension included)
 * @param data Pointer of Data Object
 */
extern int initGame(char* saveName, Data* data);

/**
 * Write the save using info of the Game
 * @param data Pointer of Data Object
 */
extern void writeSave(Data* data);

/**
 * Read the save using the name inside Player Object
 * @param data Pointer of Data Object
 */
extern void readSave(Data* data);

#endif //FREE_PROJECT_ENGINE_SAVE_H
