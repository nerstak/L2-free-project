#ifndef FREE_PROJECT_ENGINE_TIMER_H
#define FREE_PROJECT_ENGINE_TIMER_H

#include <stdbool.h>

typedef struct Timer {
    int startTicks;
    int pausedTicks;

    bool paused;
    bool started;
} Timer;

extern Timer* init_Timer();
extern void clean_Timer(Timer** myTimer);

extern void start_Timer(Timer* myTimer);
extern void stop_Timer(Timer* myTimer);
extern void pause_Timer(Timer* myTimer);
extern void unpause_Timer(Timer* myTimer);

extern int getTicks_Timer(Timer* myTimer);

extern bool isStarted_Timer(Timer* myTimer);
extern bool isPaused_Timer(Timer* myTimer);

extern float getTime_Timer(Timer* myTimer);

extern void cap_Timer(Timer * mytimer,int time);

extern int lap_Timer(Timer * mytimer);
#endif //FREE_PROJECT_ENGINE_TIMER_H
