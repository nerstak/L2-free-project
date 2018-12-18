#ifndef FREE_PROJECT_ENGINE_TIMER_H
#define FREE_PROJECT_ENGINE_TIMER_H

#include <stdbool.h>

typedef struct Timer {
    int startTicks;
    int pausedTicks;

    bool paused;
    bool started;
} Timer;

/**
 * Create a Timer object
 * @return a Timer object
 */
extern Timer* init_Timer();
/**
 * Clean a Timer object
 * @param p a double pointer to a Timer object
 */
extern void clean_Timer(Timer** myTimer);

/**
 * Start a given Timer object
 * @param myTimer a pointer to a Timer object
 */
extern void start_Timer(Timer* myTimer);
/**
 * Stop a given Timer object
 * @param myTimer a pointer to a Timer object
 */
extern void stop_Timer(Timer* myTimer);
/**
 * Pause a given Timer object
 * @param myTimer a pointer to a Timer object
 */
extern void pause_Timer(Timer* myTimer);
/**
 * Unpause a given Timer object
 * @param myTimer a pointer to a Timer object
 */
extern void unpause_Timer(Timer* myTimer);

/**
 * Get the ticks since the beginning of a given Timer object
 * @param myTimer a pointer to a Timer object
 */
extern int getTicks_Timer(Timer* myTimer);
/**
 * Get the ticks since the beginning of a given Timer object (only started and not paused)
 * @param myTimer a pointer to a Timer object
 */
extern int getTicksStart_Timer(Timer* myTimer);

/**
 * Return the status of a given Timer object
 * @param myTimer a pointer to a Timer object
 */
extern bool isStarted_Timer(Timer* myTimer);
/**
 * Return the status of a given Timer object
 * @param myTimer a pointer to a Timer object
 */
extern bool isPaused_Timer(Timer* myTimer);

/**
 * Return the time (in s) since start of a given Timer object
 * @param myTimer a pointer to a Timer object
 */
extern float getTime_Timer(Timer* myTimer);

/**
 * Auto cap a given Timer object
 * @param myTimer a pointer to a Timer object
 */
extern void cap_Timer(Timer * mytimer,int time);

/**
 * Lap a given Timer object and return the lap time in ticks
 * @param myTimer a pointer to a Timer object
 */
extern int lap_Timer(Timer * mytimer);

#endif //FREE_PROJECT_ENGINE_TIMER_H
