#ifndef FREE_PROJECT_ENGINE_MAIN_H
#define FREE_PROJECT_ENGINE_MAIN_H

#include "../engine/collectors/image.h"
#include "../engine/collectors/ttf.h"
#include "../engine/collectors/scene.h"
#include "../engine/collectors/sound.h"

typedef struct Engine {
    SceneCollector* sceneCollector;
    ImageCollector* imageCollector;
    FontCollector* fontCollector;
    SoundCollector* soundCollector;
} Engine;

extern Engine* init_Engine();
extern void clean_Engine(Engine** p);

#endif //FREE_PROJECT_ENGINE_MAIN_H
