#include "game.h"
#include "window.h"
#include "menu.h"

#include "timer.h"
#include "image.h"

#include <SDL/SDL.h>

extern void gameLoop(SDL_Surface* window) {
    int stop = 1;
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
    load_ImageCollector(myImageCollector, "src/gfx/menu/main_logo.jpg", "menu/main_logo");
    load_ImageCollector(myImageCollector, "src/gfx/menu/main_button.jpg", "menu/main_button");
    load_ImageCollector(myImageCollector, "src/gfx/menu/select.png", "menu/select");

    while (stop) {
        // Start the FPS limiter Timer
        start_Timer(fpsLimiter);

        // Event loop
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN: {
                    // Key pressed
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            // We should only leave if we're on the main menu
                            // Either way we bring the pause menu
                            stop = 0;

                            break;
                        case SDLK_UP:
                            // Move menu selector
                            // Should be through a call to a function only ! (setter)
                            moveMainMenuSelector(0);
                            break;
                        case SDLK_DOWN:
                            // Move menu selector
                            // Should be through a call to a function only ! (setter)
                            moveMainMenuSelector(1);
                            break;
                        case SDLK_RETURN:
                            // Select our menu ? For now only
                            enterMainMenu();

                            if (getCurrentMainMenuSelector() == 2) stop = 0;

                            break;
                    }

                    break;
                }

                case SDL_QUIT: {
                    stop = 0;

                    break;
                }

                default: {
                    break;
                }
            }
        }

        // Logic

        // Rendering
        displayMainMenu(window, myImageCollector);
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
}