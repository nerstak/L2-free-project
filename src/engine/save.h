#ifndef FREE_PROJECT_ENGINE_SAVE_H
#define FREE_PROJECT_ENGINE_SAVE_H

#include "../data.h"

extern void initGame(char* saveName, Data* data);
extern void write_Save(Data* data);
int read_Save(Data* data);
static void loadPlayer(Data* data);

#endif //FREE_PROJECT_ENGINE_SAVE_H
