#ifndef FREE_PROJECT_SHOPSCREEN_H
#define FREE_PROJECT_SHOPSCREEN_H

#include <stdbool.h>

#include "../../image.h"
#include "../../data.h"

#include "event.h"
#include "logic.h"
#include "render.h"

extern void assets_Scene_shop(ImageCollector* myImageCollector, bool loadOrUnload);
extern void init_Scene_shop(Data* data, bool loadOrUnload);

#endif //FREE_PROJECT_SHOPSCREEN_H
