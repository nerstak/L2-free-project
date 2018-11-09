#ifndef FREE_PROJECT_LOADINGSCREEN_H
#define FREE_PROJECT_LOADINGSCREEN_H

#include <stdbool.h>

#include "../../image.h"
#include "../../data.h"

#include "event.h"
#include "logic.h"
#include "render.h"

extern void assets_Scene_loadingScreen(ImageCollector* myImageCollector, bool loadOrUnload);
extern void init_Scene_loadingScreen(Data* data, bool loadOrUnload);

#endif //FREE_PROJECT_LOADINGSCREEN_H
