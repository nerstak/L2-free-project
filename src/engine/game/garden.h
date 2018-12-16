#ifndef FREE_PROJECT_ENGINE_GAME_GARDEN_H
#define FREE_PROJECT_ENGINE_GAME_GARDEN_H

#include "../data.h"
#include "layout.h"
#include "../main.h"

/**
 * Verify if the player is on a specific case
 * @param data Pointer of Data Object
 * @return An int corresponding to the square (0 for None, 1 for 'M' Home, 2 for 'P' Plant, 3 for 'S' Shop)
 */
extern int checkAction_Garden(Data* data);
/**
 * Choose the type of action that the player is asking in the lobby
 * @param data a pointer to a Data Object
 */
extern void doAction_Garden(Data* data);

/**
 * Process the interface of sleeping (+ passing day and saving)
 * @param data a pointer to a Data Object
 */
extern void processSleep(Data* data);
/**
 * Process actions in the garden (Planting / Entering into dungeon / Wainting)
 * @param data a pointer to a Data Object
 */
extern void processGarden(Data* data);
/**
 * Process interface for entering into dungeon
 * @param engine a pointer to an Engine Object
 * @param data a pointer to a Data Object
 */
extern void menuSelectionDungeon_Garden(Engine* engine, Data* data);
/**
 * Process interface for planting
 * @param data a pointer to a Data Object
 */
extern void menuSelectionPlanting_Garden(Data* data);
/**
 * Move to next day for plants
 * @param data a pointer to a Data Object
 */
extern void DayPass(Data* data);

#endif // FREE_PROJECT_ENGINE_GAME_GARDEN_H
