#ifndef FREE_PROJECT_ENGINE_COLLECTORS_SCENE_H
#define FREE_PROJECT_ENGINE_COLLECTORS_SCENE_H

#include <stdlib.h>
#include <stdbool.h>

#include <SDL/SDL.h>
#include "../data.h"

struct Engine;

enum sceneType {SCENE = 1, OVERLAY = 2};

typedef struct Scene {
    char name[255];
    int type;

    SDL_Surface* surface;

    /**
     * Functions
     */
    void (*renderScene)(SDL_Surface* window, struct Engine* engine, Data* data);
    void (*logicProcess)(struct Engine* engine, Data* data);
    void (*eventProcess)(SDL_Event event, struct Engine* engine, Data* data);
    void (*assets)(struct Engine* engine, Data* data, bool loadOrUnload);
    void (*init)(struct Engine* engine, Data* data, bool loadOrUnlaod);

    struct Scene* next;
} Scene;

typedef struct SceneCollector {
    size_t size;
    struct Scene* previousScene;
    struct Scene* currentScene;
    struct Scene* previousOverlay;
    struct Scene* currentOverlay;
    struct Scene* loadingScene;
    struct Scene* scenes;
} SceneCollector;

extern SceneCollector* init_SceneCollector();
extern void clean_SceneCollector(SceneCollector** mySceneCollector);

extern void load_SceneCollector(struct Engine* engine, Data* data, const char name[], int type,
        void (*assets)(struct Engine* engine, Data* data, bool loadOrUnload),
        void (*init)(struct Engine* engine, Data* data, bool loadOrUnload),
        void (*renderScene)(SDL_Surface* window, struct Engine* engine, Data* data),
        void (*logicProcess)(struct Engine* engine, Data* data),
        void (*eventProcess)(SDL_Event event, struct Engine* engine, Data* data));
extern void unload_SceneCollector(struct Engine* engine, const char name[]);

extern void display_SceneCollector(struct Engine* engine, Data* data, const char name[]);

#endif //FREE_PROJECT_ENGINE_COLLECTORS_SCENE_H
