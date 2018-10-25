#include "scene.h"

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
        clean_Data(&(temp->data));
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
        clean_Data(&(temp->data));
        free(temp);

        mySceneCollector->size -= 1;
    }
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
    mySceneCollector->loadingScene = NULL;
    mySceneCollector->scenes = NULL;

    return mySceneCollector;
}

extern void clean_SceneCollector(SceneCollector** mySceneCollector) {
    // First we clean the scenes SLL
    Scene* temp = (*mySceneCollector)->scenes;
    Scene* next = NULL;

    while (temp->next != NULL) {
        next = temp->next;

        // Clean all the properties of our scene
        SDL_FreeSurface(temp->surface);
        clean_Data(&(temp->data));
        free(temp);

        temp = next;
    }

    // We free this SceneCollector
    free(*mySceneCollector);
    (*mySceneCollector) = NULL;
}

extern void load_SceneCollector(SceneCollector* mySceneCollector, ImageCollector* myImageCollector, const char name[], void (*assets)(ImageCollector* myImageCollector, bool loadOrUnload), void (*init)(Data* data, bool loadOrUnload), void (*renderScene)(SDL_Surface* window, ImageCollector* myImageCollector, Data* data), void (*logicProcess)(Data* data), void (*eventProcess)(SDL_Event event, Data* data)) {
    // Is it already loaded ?
    if (isLoaded_SceneCollector(mySceneCollector, name) != NULL) {
        printf("An attempt to load a scene was blocked (%s)\n", name);

        return;
    }

    // Is it the loading screen ?
    if (strcmp(name, "loadingScreen") == 0) {
        // We load the assets ! (we will need them for the loading screen)
        assets(myImageCollector, true);
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
    myScene->surface = SDL_CreateRGBSurface(SDL_HWSURFACE, 1280, 720, 32, 0, 0, 0, 0);

    myScene->renderScene = renderScene;
    myScene->logicProcess = logicProcess;
    myScene->eventProcess = eventProcess;
    myScene->assets = assets;
    myScene->init = init;

    myScene->data = init_Data();

    myScene->next = NULL;

    add_Scene(mySceneCollector, myScene);
}

extern void unload_SceneCollector(SceneCollector* mySceneCollector, const char name[]) {
    Scene myScene;
    strcpy(myScene.name, name);

    // We remove one Scene from our SceneCollector
    remove_Scene(mySceneCollector, &myScene);
}

extern void display_SceneCollector(SceneCollector* mySceneCollector, ImageCollector* myImageCollector, const char name[]) {
    // We may display a waiting screen :) ?
    Scene* previousScene = mySceneCollector->currentScene;
    mySceneCollector->currentScene = mySceneCollector->loadingScene;

    // Now we do our shit behind the scene
    // First we clean the previous scene
    if (previousScene != NULL) {
        previousScene->assets(myImageCollector, false);
        previousScene->init(previousScene->data, false);
    }

    // Secondly we display the new one
    Scene* temp = mySceneCollector->scenes;

    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            temp->assets(myImageCollector, true);
            temp->init(temp->data, true);
            // We hide it
            mySceneCollector->currentScene = temp;

            return;
        }

        temp = temp->next;
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