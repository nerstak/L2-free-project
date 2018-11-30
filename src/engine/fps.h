#ifndef FREE_PROJECT_ENGINE_FPS_H
#define FREE_PROJECT_ENGINE_FPS_H

#include <stdbool.h>

#include "timer.h"

typedef struct Fps {
    Timer* limiter;
    Timer* counter;
    Timer* display;

    bool fpsLimited;
    int maxFps;

    int currentFps;
    int frame;
} Fps;

/**
 * Create a Fps object
 * @return a Fps object
 */
extern Fps* init_Fps();
/**
 * Clean a Fps object
 * @param p a double pointer to a Fps object
 */
extern void clean_Fps(Fps** p);

/**
 * Return the status of the fps limitation
 * @param p a pointer to a Fps object
 * @return a boolean depending of the result
 */
extern bool isFpsLimited_Fps(Fps* p);
/**
 * Get the maxFps current value (-1 = unlimited)
 * @param p a pointer to a Fps object
 * @return a integer representing the fps limitation
 */
extern int getMaxFps_Fps(Fps* p);
/**
 * Set the limitation of our Fps
 * @param p a pointer to a Fps object
 * @param enabled a boolean enabling or disabling the limiter
 * @param maxFps a integer representing the maxFps value
 */
extern void setMaxFps_Fps(Fps* p, bool enabled, int maxFps);

/**
 * Start the counter Timer
 * @param p a pointer to a Fps object
 */
extern void startCounterTimer_Fps(Fps* p);
/**
 * Start the display Timer
 * @param p a pointer to a Fps object
 */
extern void startDisplayTimer_Fps(Fps* p);
/**
 * Start the limiter Timer
 * @param p a pointer to a Fps object
 */
extern void startLimiterTimer_Fps(Fps* p);

/**
 * Limit the Fps using the settings of our object
 * @param p a pointer to a Fps object
 */
extern void limit_Fps(Fps* p);
/**
 * Count the Fps
 * @param p a pointer to a Fps object
 */
extern void count_Fps(Fps* p);

#endif //FREE_PROJECT_ENGINE_FPS_H
