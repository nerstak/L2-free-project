#include "game.h"
#include "window.h"
#include "menu.h"

#include "timer.h"

#include <SDL/SDL.h>

extern void gameLoop(SDL_Surface* window) {
    int stop = 1;
    SDL_Event event;

    int frame = 0;
    Timer* fps = init_Timer();
    Timer* update = init_Timer();

    int currentView = 1; // 1: mainMenu

    // Start the FPS Timer
    start_Timer(fps);
    // Start the update timer
    start_Timer(update);

    while (stop) {
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
        displayMainMenu(window);
        renderScreen();
        frame++;

        // FPS counter
        if (getTicks_Timer(update) > 1000) {
            printf("FPS %d\n", frame / ((getTicks_Timer(fps) / 1000)));
            start_Timer(update);
        }

        // FPS Limiter
        if (getTicks_Timer(fps) < 1000 / 60) {
            SDL_Delay((1000 / 60) - getTicks_Timer(fps));
        }
    }
}