#ifndef FREE_PROJECT_GARDEN_H
#define FREE_PROJECT_GARDEN_H

#include "data.h"

extern int checkAction_Garden(Data* data);
extern void doAction_Garden(Data* data);

extern void processMenu1_Garden(Data* data);
extern void processMenu2_Garden(Data* data);
extern void processField_Garden(Data* data);
extern void menuSelectionDonjon_Garden(Data* data);
extern void menuSelectionPlanting_Garden(Data* data);
extern void menuNotReady_Garden(Data* data);

#endif // FREE_PROJECT_GARDEN_H
