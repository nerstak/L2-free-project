#include "scene.h"

#include "../main.h"

static void add_Scene(SceneCollector* mySceneCollector, Scene* myScene);
static void remove_Scene(SceneCollector* mySceneCollector, Scene* myScene);

static Scene* isLoaded_SceneCollector(SceneCollector* mySceneCollector, const char name[]);

static void add_Scene(SceneCollector* mySceneCollector, Scene* myScene) {
    // Is our list of images empty ?
    if (mySceneCollector->scenes == NULL) {
        // We write directly to the pointer
        mySceneCollector->scenes = myScene;
        mySceneCollector->size += 1;
    } else {
        // We find the last element of the list
        Scene* temp = NULL;
        temp = mySceneCollector->scenes;

        while (temp->next != NULL) {
            temp = temp->next;
        }

        // We add our element
        temp->next = myScene;
        mySceneCollector->size += 1;
    }

    // Is it the loadingScreen scene ?
    if (strcmp(myScene->name, "loadingScreen") == 0) {
        mySceneCollector->loadingScene = myScene;
    }
}

static void remove_Scene(SceneCollector* mySceneCollector, Scene* myScene) {
    Scene* temp = mySceneCollector->scenes;
    Scene* previous = mySceneCollector->scenes;

    // Is the element we want to remove the first one ?
    if (strcmp(temp->name, myScene->name) == 0) {
        // We rewrite the head of our list
        mySceneCollector->scenes = temp->next;
        mySceneCollector->size -= 1;

        // Don't forget to free the surface and the memory :D
        SDL_FreeSurface(temp->surface);
        free(temp);
    } else {
        // We find the position of the element we want to remove
        while (temp != NULL && strcmp(temp->name, myScene->name) != 0) {
            previous = temp;
            temp = temp->next;
        }

        if (temp == NULL) {
            return;
        }

        // Relink our list
        previous->next = temp->next;

        // Clean all the properties of our scene
        SDL_FreeSurface(temp->surface);
        free(temp);

        mySceneCollector->size -= 1;
    }
}

static Scene* isLoaded_SceneCollector(SceneCollector* mySceneCollector, const char name[]) {
    Scene* temp = mySceneCollector->scenes;

    // We retrieve the existing Scene from our SceneCollector
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            return temp;
        }

        temp = temp->next;
    }

    // Or we return NULL
    return NULL;
}

extern SceneCollector* init_SceneCollector() {
    // Initialization of a SceneCollector pointer
    SceneCollector* mySceneCollector = NULL;
    mySceneCollector = malloc(1 * sizeof(SceneCollector));

    // If we failed to allocate, exit the program
    if (mySceneCollector == NULL) {
        printf("An error occured while initializing a SceneCollector object\n");
        exit(EXIT_FAILURE);
    }

    // Default value of our instance
    mySceneCollector->size = 0;
    mySceneCollector->currentScene = NULL;
    mySceneCollector->previousScene = NULL;
    mySceneCollector->currentOverlay = NULL;
    mySceneCollector->previousOverlay = NULL;
    mySceneCollector->loadingScene = NULL;
    mySceneCollector->scenes = NULL;

    return mySceneCollector;
}

extern void clean_SceneCollector(SceneCollector** mySceneCollector) {
    // First we clean the scenes SLL
    Scene* temp = (*mySceneCollector)->scenes;
    Scene* next = NULL;

    while (temp != NULL) {
        next = temp->next;

        // Clean all the properties of our scene
        SDL_FreeSurface(temp->surface);
        free(temp);

        temp = next;
    }

    // We free this SceneCollector
    free(*mySceneCollector);
    (*mySceneCollector) = NULL;
}

extern void load_SceneCollector(struct Engine* engine, Data* data, const char name[], int type,
                                void (*assets)(struct Engine* engine, Data* data, bool loadOrUnload),
                                void (*init)(struct Engine* engine, Data* data, bool loadOrUnload),
                                void (*renderScene)(SDL_Surface* window, struct Engine* engine, Data* data),
                                void (*logicProcess)(struct Engine* engine, Data* data),
                                void (*eventProcess)(SDL_Event event, struct Engine* engine, Data* data)) {
    // Is it already loaded ?
    if (isLoaded_SceneCollector(engine->sceneCollector, name) != NULL) {
        printf("An attempt to load a scene was blocked (%s)\n", name);

        return;
    }

    // Is it the loading screen ?
    if (strcmp(name, "loadingScreen") == 0) {
        // We load the assets ! (we will need them for the loading screen)
        assets(engine, data, true);
    }

    // We allocate a Scene instance
    Scene* myScene = NULL;
    myScene = malloc(1 * sizeof(Scene));

    if (myScene == NULL) {
        printf("An error occured while initializing a Scene object\n");
        exit(EXIT_FAILURE);
    }

    // We configure our Scene
    strcpy(myScene->name, name);
    myScene->type = type;
    myScene->surface = SDL_CreateRGBSurface(SDL_HWSURFACE, 1280, 720, 32, 0, 0, 0, 0);

    myScene->renderScene = renderScene;
    myScene->logicProcess = logicProcess;
    myScene->eventProcess = eventProcess;
    myScene->assets = assets;
    myScene->init = init;

    myScene->next = NULL;

    add_Scene(engine->sceneCollector, myScene);
}

extern void unload_SceneCollector(struct Engine* engine, const char name[]) {
    Scene myScene;
    strcpy(myScene.name, name);

    // We remove one Scene from our SceneCollector
    remove_Scene(engine->sceneCollector, &myScene);
}

extern void display_SceneCollector(struct Engine* engine, Data* data, const char name[]) {
    // Find the new scene
    Scene* temp = engine->sceneCollector->scenes;

    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            break;
        }

        temp = temp->next;
    }

    if (temp == NULL) {
        // TODO: Fail err, scene not found
        exit(EXIT_FAILURE);
    }

    // Display the loading screen
    Scene* previousScene = NULL;

    if (engine->sceneCollector->currentOverlay != NULL) { // An overlay is active
        previousScene = engine->sceneCollector->previousScene;
        engine->sceneCollector->currentScene = engine->sceneCollector->loadingScene;
    } else if (engine->sceneCollector->currentScene != NULL) { // A scene is active
        previousScene = engine->sceneCollector->currentScene;
        engine->sceneCollector->currentScene = engine->sceneCollector->loadingScene;
        engine->sceneCollector->previousScene = previousScene;
    }

    // Currently there is an overlay displayed
    if (engine->sceneCollector->currentOverlay != NULL) {
        if (temp->type == OVERLAY) { // Sub overlay
            if (temp == engine->sceneCollector->previousOverlay) { // Going back
                engine->sceneCollector->currentOverlay->assets(engine, data, false);
                engine->sceneCollector->currentOverlay->init(engine, data, false);

                engine->sceneCollector->currentOverlay = temp;
            } else {
                temp->assets(engine, data, true);
                temp->init(engine, data, true);

                engine->sceneCollector->previousOverlay = engine->sceneCollector->currentOverlay;
                engine->sceneCollector->currentOverlay = temp;
            }
        } else if (temp->type == SCENE) { // Leaving overlay
            engine->sceneCollector->currentOverlay->assets(engine, data, false);
            engine->sceneCollector->currentOverlay->init(engine, data, false);

            if (engine->sceneCollector->previousOverlay != NULL) {
                engine->sceneCollector->previousOverlay->assets(engine, data, false);
                engine->sceneCollector->previousOverlay->init(engine, data, false);

                engine->sceneCollector->previousOverlay = NULL;
            }

            if(strcmp(previousScene->name, temp->name) != 0) {
                previousScene->assets(engine, data, false);
                previousScene->init(engine, data, false);

                temp->assets(engine, data, true);
                temp->init(engine, data, true);
            }
            engine->sceneCollector->currentScene = temp;

            engine->sceneCollector->currentOverlay = NULL;
        }
    } else if (engine->sceneCollector->previousScene != NULL) { // Currently there is a scene displayed
        if (temp->type == SCENE) {
            engine->sceneCollector->previousScene->assets(engine, data, false);
            engine->sceneCollector->previousScene->init(engine, data, false);

            temp->assets(engine, data, true);
            temp->init(engine, data, true);

            engine->sceneCollector->currentScene = temp;
        } else if (temp->type == OVERLAY) {
            temp->assets(engine, data, true);
            temp->init(engine, data, true);

            engine->sceneCollector->currentScene = NULL;
            engine->sceneCollector->currentOverlay = temp;
        }
    } else { // Nothing was displayed
        if (temp->type == SCENE) {
            temp->assets(engine, data, true);
            temp->init(engine, data, true);

            engine->sceneCollector->currentScene = temp;
        } else if (temp->type == OVERLAY) {
            // TODO: Error can't start with a OVERLAY
        }
    }
}