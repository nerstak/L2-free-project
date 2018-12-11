#include <stdlib.h>
#include <stdio.h>

#include "SDL/SDL.h"

#include "timer.h"

extern Timer* init_Timer() {
    // Initialization of a Timer pointer
    Timer* myTimer = NULL;
    myTimer = malloc(1 * sizeof(Timer));

    // If we failed to allocate, exit the program
    if (myTimer == NULL) {
        printf("An error occured while initializing a Timer object");
        exit(EXIT_FAILURE);
    }

    // Default value of our instance
    myTimer->startTicks = 0;
    myTimer->pausedTicks = 0;
    myTimer->started = false;
    myTimer->pausedTicks = false;

    return myTimer;
}

extern void clean_Timer(Timer** myTimer) {
    // First we free the memory
    free(*(myTimer));
    // We set the pointer to NULL by security
    *(myTimer) = NULL;
}

extern void start_Timer(Timer* myTimer) {
    // We start our Timer by updating his instance
    myTimer->started = true;
    myTimer->paused = false;
    myTimer->startTicks = SDL_GetTicks();
}

extern void stop_Timer(Timer* myTimer) {
    // We stop our Timer by updating his instance
    myTimer->started = false;
    myTimer->paused = false;
}

extern void pause_Timer(Timer* myTimer) {
    // Is our Timer running ?
    if (myTimer->started == true && myTimer->paused == false) {
        // We pause our Timer
        myTimer->paused = true;
        // We get the ticks between the beginning and this moment
        myTimer->pausedTicks = SDL_GetTicks() - myTimer->startTicks;
    }
}

extern void unpause_Timer(Timer* myTimer) {
    // Is our Timer paused ?
    if (myTimer->paused == true) {
        // We pause our Timer
        myTimer->paused = false;
        // We update the startTicks
        myTimer->startTicks = SDL_GetTicks() - myTimer->pausedTicks;
        // We reset the pausedTicks
        myTimer->pausedTicks = 0;
    }
}

extern int getTicks_Timer(Timer* myTimer) {
    // Is our Timer running ?
    if (myTimer->started == true) {
        // Is our Timer paused ?
        if (myTimer->paused == true) {
            // We return the pausedTicks
            return myTimer->pausedTicks;
        } else {
            // We return the ticks since the start
            return SDL_GetTicks() - myTimer->startTicks;
        }
    }

    return 0;
}

extern bool isStarted_Timer(Timer* myTimer) {
    // Return the status of our Timer
    return myTimer->started;
}

extern bool isPaused_Timer(Timer* myTimer) {
    // Return the status of our Timer
    return myTimer->paused;
}

extern float getTime_Timer(Timer* myTimer) {
    // Return time that passed since the init of the timer in secondss
    return (float) getTicks_Timer(myTimer) / 1000;
}


extern void cap_Timer(Timer * mytimer,int time){
    if(mytimer->started)
    {
        if(getTicks_Timer(mytimer)>time)
        {
            stop_Timer(mytimer);
        }
    }
}

extern int lap_Timer(Timer * mytimer)
{
    int timeVal=getTicks_Timer(mytimer);
    stop_Timer(mytimer);
    start_Timer(mytimer);
    return timeVal;
}

