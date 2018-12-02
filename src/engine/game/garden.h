#ifndef FREE_PROJECT_ENGINE_GAME_GARDEN_H
#define FREE_PROJECT_ENGINE_GAME_GARDEN_H

#include "../data.h"
#include "layout.h"

/**
 * Verify if the player is on a specific case
 * @param data Pointer of Data Object
 * @return An int corresponding to the square (0 for None, 1 for 'M' Home, 2 for 'P' Plant, 3 for 'S' Shop)
 */
extern int checkAction_Garden(Data* data);
extern void doAction_Garden(Data* data);

extern void processMenu1_Garden(Data* data);
extern void processMenu2_Garden(Data* data);
extern void processField_Garden(Data* data);
extern void menuSelectionDungeon_Garden(Data* data);
extern void menuSelectionPlanting_Garden(Data* data);
extern void menuNotReady_Garden(Data* data);
extern void DayPass(Data* data);

#endif // FREE_PROJECT_ENGINE_GAME_GARDEN_H
