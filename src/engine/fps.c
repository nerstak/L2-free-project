#include "fps.h"

#include <stdlib.h>
#include <stdio.h>

#include <SDL/SDL.h>

extern Fps* init_Fps() {
    // Initialization of a Fps pointer
    Fps* p = NULL;
    p = malloc(1 * sizeof(Fps));

    // If we failed to allocate, exit the program
    if (p == NULL) {
        printf("An error occurred while initializing a Fps object");
        exit(EXIT_FAILURE);
    }

    p->counter = init_Timer();
    p->limiter = init_Timer();
    p->display = init_Timer();

    p->fpsLimited = false;
    p->maxFps = -1;

    p->currentFps = 0;
    p->frame = 0;

    start_Timer(p->counter);
    start_Timer(p->display);

    return p;
}

extern void clean_Fps(Fps** p) {
    if ((*p) != NULL) {
        clean_Timer(&((*p)->limiter));
        clean_Timer(&((*p)->counter));

        free((*p));
        (*p) = NULL;
    }
}


extern bool isFpsLimited_Fps(Fps* p) {
    return p->fpsLimited;
}

extern int getMaxFps_Fps(Fps* p) {
    return p->maxFps;
}

extern void setMaxFps_Fps(Fps* p, bool enabled, int maxFps) {
    if(maxFps == -1) {
        p->fpsLimited = false;
    } else {
        p->fpsLimited = true;
    }
    p->maxFps = maxFps;

}

extern void startCounterTimer_Fps(Fps* p) {
    start_Timer(p->counter);
}

extern void startDisplayTimer_Fps(Fps* p) {
    start_Timer(p->display);
}

extern void startLimiterTimer_Fps(Fps* p) {
    start_Timer(p->limiter);
}


extern void limit_Fps(Fps* p) {
    if (p->maxFps != -1) {
        if (getTicks_Timer(p->limiter) < (1000 / p->maxFps)) {
            SDL_Delay((Uint32) ((1000 / p->maxFps) - getTicks_Timer(p->limiter)));
        }
    }
}

extern void count_Fps(Fps* p) {
    p->frame += 1;

    if (getTicks_Timer(p->display) > 1000) {
        p->currentFps = p->frame / (getTicks_Timer(p->counter) / 1000);
        start_Timer(p->display);
    }
}