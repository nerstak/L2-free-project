#include "game.h"
#include "window.h"

#include "timer.h"
#include "image.h"
#include "scene.h"

#include "scenes/mainMenu.h"
#include "scenes/loadingScreen.h"

#include <SDL/SDL.h>

/**
 * Global variables (use with caution please)
 */
int Game_stop = 1; // External

extern void gameLoop(SDL_Surface* window) {
    SDL_Event event;

    int frame = 0;
    Timer* fpsLimiter = init_Timer();
    Timer* fpsCounter = init_Timer();
    Timer* update = init_Timer();

    int currentView = 1; // 1: mainMenu

    // Start the update Timer
    start_Timer(update);

    // Start the fps counter Timer
    start_Timer(fpsCounter);

    // Initializing ImageCollector
    ImageCollector* myImageCollector = init_ImageCollector();

    // Initializing SceneCollector
    SceneCollector* mySceneCollector = init_SceneCollector();
    load_SceneCollector(mySceneCollector, myImageCollector, "loadingScreen", &assets_Scene_loadingScreen, &renderScene_Scene_loadingScreen, &logicProcess_Scene_loadingScreen, &eventProcess_Scene_loadingScreen);
    load_SceneCollector(mySceneCollector, myImageCollector, "mainMenu", &assets_Scene_mainMenu, &renderScene_Scene_mainMenu, &logicProcess_Scene_mainMenu, &eventProcess_Scene_mainMenu);

    display_SceneCollector(mySceneCollector, myImageCollector, "mainMenu");

    while (Game_stop) {
        // Start the FPS limiter Timer
        start_Timer(fpsLimiter);

        // Event loop
        while (SDL_PollEvent(&event)) {
            mySceneCollector->currentScene->eventProcess(event, mySceneCollector->currentScene->data);

            switch (event.type) {
                case SDL_KEYDOWN: {
                    // Key pressed
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            // We should only leave if we're on the main menu
                            // Either way we bring the pause menu
                            Game_stop = 0;

                            break;
                    }

                    break;
                }

                case SDL_QUIT: {
                    Game_stop = 0;

                    break;
                }

                default: {
                    break;
                }
            }
        }

        // Logic
        mySceneCollector->currentScene->logicProcess(mySceneCollector->currentScene->data);

        // Rendering
        mySceneCollector->currentScene->renderScene(window, myImageCollector, mySceneCollector->currentScene->data);
        renderScreen();
        frame++;

        // FPS counter
        if (getTicks_Timer(update) > 1000) {
            printf("FPS %d\n", frame / ((getTicks_Timer(fpsCounter) / 1000)));
            start_Timer(update);
        }

        // FPS Limiter
        if (getTicks_Timer(fpsLimiter) < (1000 / 60)) {
            SDL_Delay((1000 / 60) - getTicks_Timer(fpsLimiter));
        }
    }

    clean_Timer(&fpsLimiter);
    clean_Timer(&fpsCounter);
    clean_Timer(&update);

    clean_ImageCollector(&myImageCollector);
    clean_SceneCollector(&mySceneCollector);
}