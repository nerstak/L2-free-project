#ifndef FREE_PROJECT_MAINMENU_H
#define FREE_PROJECT_MAINMENU_H

#include <stdbool.h>

#include "../../image.h"
#include "../../data.h"

#include "event.h"
#include "logic.h"
#include "render.h"

extern void assets_Scene_mainMenu(ImageCollector* myImageCollector, bool loadOrUnload);
extern void init_Scene_mainMenu(Data* data, bool loadOrUnload);

#endif //FREE_PROJECT_MAINMENU_H
