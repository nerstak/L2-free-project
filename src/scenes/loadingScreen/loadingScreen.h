#ifndef FREE_PROJECT_LOADINGSCREEN_H
#define FREE_PROJECT_LOADINGSCREEN_H

#include <stdbool.h>

#include "../../engine/collectors/image.h"
#include "../../engine/data.h"

#include "event.h"
#include "logic.h"
#include "render.h"

extern void assets_Scene_loadingScreen(Engine* engine, Data* data, bool loadOrUnload);
extern void init_Scene_loadingScreen(Engine* engine, Data* data, bool loadOrUnload);

#endif //FREE_PROJECT_LOADINGSCREEN_H
