#ifndef FREE_PROJECT_STRUCTURES_SCENE_H
#define FREE_PROJECT_STRUCTURES_SCENE_H

#include <stdbool.h>
#include <SDL/SDL.h>

#include "../data.h"
#include "../engine/main.h"

enum sceneType {SCENE = 1, OVERLAY = 2};

typedef struct Scene {
    char name[255];
    int type;

    SDL_Surface* surface;

    /**
     * Functions
     */
    void (*renderScene)(SDL_Surface* window, Engine* engine, Data* data);
    void (*logicProcess)(Engine* engine, Data* data);
    void (*eventProcess)(SDL_Event event, Engine* engine, Data* data);
    void (*assets)(Engine* engine, Data* data, bool loadOrUnload);
    void (*init)(Engine* engine, Data* data, bool loadOrUnlaod);

    struct Scene* next;
} Scene;

#endif //FREE_PROJECT_STRUCTURES_SCENE_H
