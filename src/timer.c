#include <stdlib.h>
#include <stdio.h>

#include "SDL/SDL.h"

#include "timer.h"

Timer* init_Timer() {
    Timer* myTimer = NULL;
    myTimer = malloc(1 * sizeof(myTimer));

    if (myTimer == NULL) {
        printf("An error occured while initializing a Timer object");
        exit(EXIT_FAILURE);
    }

    myTimer->startTicks = 0;
    myTimer->pausedTicks = 0;
    myTimer->started = false;
    myTimer->pausedTicks = false;

    return myTimer;
}

void clean_Timer(Timer** myTimer) {
    free(*(myTimer));
    *(myTimer) = NULL;
}

void start_Timer(Timer* myTimer) {
    myTimer->started = true;
    myTimer->paused = false;
    myTimer->startTicks = SDL_GetTicks();
}

void stop_Timer(Timer* myTimer) {
    myTimer->started = false;
    myTimer->paused = false;
}

void pause_Timer(Timer* myTimer) {
    if (myTimer->started == true && myTimer->paused == false) {
        myTimer->paused = true;
        myTimer->pausedTicks = SDL_GetTicks() - myTimer->startTicks;
    }
}

void unpause_Timer(Timer* myTimer) {
    if (myTimer->paused == true) {
        myTimer->paused = false;
        myTimer->startTicks = SDL_GetTicks() - myTimer->pausedTicks;
        myTimer->pausedTicks = 0;
    }
}

int getTicks_Timer(Timer* myTimer) {
    if (myTimer->started == true) {
        if (myTimer->paused == true) {
            return myTimer->pausedTicks;
        } else {
            return SDL_GetTicks() - myTimer->startTicks;
        }
    }

    return 0;
}

bool isStarted_Timer(Timer* myTimer) {
    return myTimer->started;
}

bool isPaused_Timer(Timer* myTimer) {
    return myTimer->paused;
}