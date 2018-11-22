#ifndef FREE_PROJECT_TEST_TEST_H
#define FREE_PROJECT_TEST_TEST_H

#include <stdbool.h>

#include "../../image.h"
#include "../../data.h"

#include "event.h"
#include "logic.h"
#include "render.h"

extern void assets_Scene_test(ImageCollector* myImageCollector, bool loadOrUnload);
extern void init_Scene_test(Data* data, bool loadOrUnload);

#endif //FREE_PROJECT_TEST_TEST_H
