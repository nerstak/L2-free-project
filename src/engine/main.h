#ifndef FREE_PROJECT_ENGINE_MAIN_H
#define FREE_PROJECT_ENGINE_MAIN_H

#include "../engine/collectors/image.h"
#include "../engine/collectors/ttf.h"
#include "../engine/collectors/scene.h"
#include "../engine/collectors/sound.h"
#include "fps.h"
#include "controller.h"

typedef struct Engine {
    Fps* fps;
    referenceKey* keys;
    int volumeSFX;
    int volumeMusic;

    SceneCollector* sceneCollector;
    ImageCollector* imageCollector;
    FontCollector* fontCollector;
    SoundCollector* soundCollector;
} Engine;

/**
 * Create a Engine object
 * @return a Engine object
 */
extern Engine* init_Engine();
/**
 * Clean a Engine object
 * @param p a double pointer to a Engine object
 */
extern void clean_Engine(Engine** p);

#endif //FREE_PROJECT_ENGINE_MAIN_H
