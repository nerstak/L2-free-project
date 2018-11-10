#ifndef FREE_PROJECT_ENGINE_MAIN_H
#define FREE_PROJECT_ENGINE_MAIN_H

#include "../engine/collectors/image.h"
#include "../engine/collectors/ttf.h"
#include "../engine/collectors/scene.h"

typedef struct Engine {
    SceneCollector* sceneCollector;
    ImageCollector* imageCollector;
    FontCollector* fontCollector;
} Engine;

extern Engine* init_Engine();
extern void clean_Engine(Engine** p);

#endif //FREE_PROJECT_ENGINE_MAIN_H
