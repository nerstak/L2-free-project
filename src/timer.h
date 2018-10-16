#include <stdbool.h>

#ifndef FREE_PROJECT_TIMER_H
#define FREE_PROJECT_TIMER_H

typedef struct Timer {
    int startTicks;
    int pausedTicks;

    bool paused;
    bool started;
} Timer;

Timer* init_Timer();
void clean_Timer(Timer** myTimer);

void start_Timer(Timer* myTimer);
void stop_Timer(Timer* myTimer);
void pause_Timer(Timer* myTimer);
void unpause_Timer(Timer* myTimer);

int getTicks_Timer(Timer* myTimer);

bool isStarted_Timer(Timer* myTimer);
bool isPaused_Timer(Timer* myTimer);

#endif //FREE_PROJECT_TIMER_H
