#ifndef FREE_PROJECT_LOBBY_H
#define FREE_PROJECT_LOBBY_H

#include <stdbool.h>

#include "../../engine/collectors/image.h"
#include "../../engine/data.h"

#include "event.h"
#include "logic.h"
#include "render.h"

extern void assets_Scene_lobby(Engine* engine, Data* data, bool loadOrUnload);
extern void init_Scene_lobby(Engine* engine, Data* data, bool loadOrUnload);

#endif //FREE_PROJECT_LOBBY_H
