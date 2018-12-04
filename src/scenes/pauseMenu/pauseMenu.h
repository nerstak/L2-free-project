#ifndef FREE_PROJECT_PAUSEMENU_PAUSEMENU_H
#define FREE_PROJECT_PAUSEMENU_PAUSEMENU_H

#include <stdbool.h>

#include "../../engine/data.h"

#include "event.h"
#include "logic.h"
#include "render.h"

extern void assets_Scene_pauseMenu(Engine* engine, Data* data, bool loadOrUnload);
extern void init_Scene_pauseMenu(Engine* engine, Data* data, bool loadOrUnload);

#endif
