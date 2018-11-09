#ifndef FREE_PROJECT_LOBBY_H
#define FREE_PROJECT_LOBBY_H

#include <stdbool.h>

#include "../../image.h"
#include "../../data.h"

#include "event.h"
#include "logic.h"
#include "render.h"

extern void assets_Scene_lobby(ImageCollector* myImageCollector, bool loadOrUnload);
extern void init_Scene_lobby(Data* data, bool loadOrUnload);

#endif //FREE_PROJECT_LOBBY_H
