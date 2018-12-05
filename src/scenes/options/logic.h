#ifndef FREE_PROJECT_OPTIONS_LOGIC_H
#define FREE_PROJECT_OPTIONS_LOGIC_H

#include "../../engine/data.h"
#include "../../engine/main.h"

extern void logicProcess_Scene_options(Engine* engine, Data* data);
extern int preSelectFPS(Engine* engine, Data* data);
extern int preSelectSound(Engine* engine, Data* data, int actualValue);

#endif
