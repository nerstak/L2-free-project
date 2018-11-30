#include "game.h"

#include <SDL/SDL.h>

#include "window.h"

#include "engine/main.h"
#include "engine/fps.h"
#include "engine/collectors/image.h"
#include "engine/collectors/ttf.h"
#include "engine/collectors/scene.h"
#include "engine/collectors/sound.h"

#include "scenes/loadingScreen/loadingScreen.h"
#include "scenes/mainMenu/mainMenu.h"
#include "scenes/options/options.h"
#include "scenes/lobby/lobby.h"
#include "scenes/inventory/inventory.h"
#include "scenes/shop/shop.h"
#include "scenes/test/test.h"

#include "structures/scene.h"

/**
 * Global variables (use with caution please)
 */

extern void gameLoop(SDL_Surface* window) {
    SDL_Event event;

    // Initializing Fps
    Fps* myFps = init_Fps();

    // Initializing ImageCollector
    ImageCollector* myImageCollector = init_ImageCollector();

    // Initializing FontCollector
    FontCollector* myFontCollector = init_FontCollector();
    load_FontCollector(myFontCollector, "src/resources/fonts/YellowSwamp.ttf", 20, "menu/20");
    load_FontCollector(myFontCollector, "src/resources/fonts/YellowSwamp.ttf", 25, "menu/25");
    load_FontCollector(myFontCollector, "src/resources/fonts/YellowSwamp.ttf", 30, "menu/30");
    load_FontCollector(myFontCollector, "src/resources/fonts/YellowSwamp.ttf", 35, "menu/35");
    load_FontCollector(myFontCollector, "src/resources/fonts/YellowSwamp.ttf", 40, "menu/40");
    load_FontCollector(myFontCollector, "src/resources/fonts/YellowSwamp.ttf", 50, "menu/50");
    load_FontCollector(myFontCollector, "src/resources/fonts/YellowSwamp.ttf", 65, "menu/65");

    // Initializing SoundCollector
    SoundCollector* mySoundCollector = init_SoundCollector();

    // Initializing SceneCollector
    SceneCollector* mySceneCollector = init_SceneCollector();

    // Initializing Engine
    Engine* myEngine = init_Engine();
    myEngine->fps = myFps;
    myEngine->sceneCollector = mySceneCollector;
    myEngine->fontCollector = myFontCollector;
    myEngine->imageCollector = myImageCollector;
    myEngine->soundCollector = mySoundCollector;

    // Initializing Data
    Data* myData = init_Data();

    // Loading Scenes
    load_SceneCollector(myEngine, myData, "loadingScreen", SCENE, &assets_Scene_loadingScreen, &init_Scene_loadingScreen, &renderScene_Scene_loadingScreen, &logicProcess_Scene_loadingScreen, &eventProcess_Scene_loadingScreen);
    load_SceneCollector(myEngine, myData, "mainMenu", SCENE, &assets_Scene_mainMenu, &init_Scene_mainMenu, &renderScene_Scene_mainMenu, &logicProcess_Scene_mainMenu, &eventProcess_Scene_mainMenu);
    load_SceneCollector(myEngine, myData, "lobby", SCENE, &assets_Scene_lobby, &init_Scene_lobby, &renderScene_Scene_lobby, &logicProcess_Scene_lobby, &eventProcess_Scene_lobby);
    load_SceneCollector(myEngine, myData, "shop", OVERLAY, &assets_Scene_shop, &init_Scene_shop, &renderScene_Scene_shop, &logicProcess_Scene_shop, &eventProcess_Scene_shop);
    load_SceneCollector(myEngine, myData, "inventory", OVERLAY, &assets_Scene_inventory, &init_Scene_inventory, &renderScene_Scene_inventory, &logicProcess_Scene_inventory, &eventProcess_Scene_inventory);
    load_SceneCollector(myEngine, myData, "test", SCENE, &assets_Scene_test, &init_Scene_test, &renderScene_Scene_test, &logicProcess_Scene_test, &eventProcess_Scene_test);

    display_SceneCollector(myEngine, myData, "mainMenu");

    while (myData->stop) {
        // Start the FPS limiter Timer
        startLimiterTimer_Fps(myFps);

        // Event loop
        mySceneCollector->currentScene->eventProcess(event, myEngine, myData);

        // Logic
        mySceneCollector->currentScene->logicProcess(myEngine, myData);

        // Rendering
        mySceneCollector->currentScene->renderScene(window, myEngine, myData);
        renderScreen();

        count_Fps(myFps);
        limit_Fps(myFps);
    }

    clean_Fps(&myFps);

    clean_ImageCollector(&myImageCollector);
    clean_SceneCollector(&mySceneCollector);
    clean_FontCollector(&myFontCollector);
    clean_SoundCollector(&mySoundCollector);
    clean_Data(&myData);
    clean_Engine(&myEngine);
}