#ifndef FREE_PROJECT_SAVE_H
#define FREE_PROJECT_SAVE_H
#include "data.h"

Data * init_save(char * save_name);
void write_save(Data *data);
int read_save(Data *data);

#endif //FREE_PROJECT_SAVE_H
