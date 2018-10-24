#include <stdlib.h>
#include <stdbool.h>
#include <SDL/SDL.h>
#include "image.h"
#include "asset.h"
#include "data.h"

#ifndef FREE_PROJECT_SCENE_H
#define FREE_PROJECT_SCENE_H

typedef struct Scene {
    char name[255];

    SDL_Surface* surface;
     Data* data;

    /**
     * Functions
     */
    void (*renderScene)(SDL_Surface* window, ImageCollector* myImageCollector, Data* data);
    void (*logicProcess)(Data* data);
    void (*eventProcess)(SDL_Event event, Data* data);
    void (*assets)(ImageCollector* myImageCollector, bool loadOrUnload);

    struct Scene* next;
} Scene;

typedef struct SceneCollector {
    size_t size;
    Scene* currentScene;
    Scene* loadingScene;
    Scene* scenes;
} SceneCollector;

static void add_Scene(SceneCollector* mySceneCollector, Scene* myScene);
static void remove_Scene(SceneCollector* mySceneCollector, Scene* myScene);

extern SceneCollector* init_SceneCollector();
extern void clean_SceneCollector(SceneCollector** mySceneCollector);

extern void load_SceneCollector(SceneCollector* mySceneCollector, ImageCollector* myImageCollector, const char name[], void (*assets)(ImageCollector* myImageCollector, bool loadOrUnload), void (*renderScene)(SDL_Surface* window, ImageCollector* myImageCollector, Data* data), void (*logicProcess)(Data* data), void (*eventProcess)(SDL_Event event, Data* data));
extern void unload_SceneCollector(SceneCollector* mySceneCollector, const char name[]);

extern void display_SceneCollector(SceneCollector* mySceneCollector, ImageCollector* myImageCollector, const char name[]);
static Scene* isLoaded_SceneCollector(SceneCollector* mySceneCollector, const char name[]);

#endif //FREE_PROJECT_SCENE_H
