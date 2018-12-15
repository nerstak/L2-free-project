#ifndef FREE_PROJECT_UTILS_MATH_H
#define FREE_PROJECT_UTILS_MATH_H

#include <stdbool.h>

/**
 * Return the max value between 2 integers
 * @param x the first value
 * @param y the second value
 * @return the max value between x and y
 */
extern int max(int x, int y);
/**
 * Return the max value between 2 doubles
 * @param x the first value
 * @param y the second value
 * @return the max value between x and y
 */
extern double maxDouble(double x, double y);
/**
 * Return the min value between 2 integers
 * @param x the first value
 * @param y the second value
 * @return the min value between x and y
 */
extern int min(int x, int y);
/**
 * Return the sign of the double
 * @param x the value
 * @return +1 or -1
 */
extern int sign(double x);
/**
 * Return true if the probability is matched
 * @param p the probability
 * @return a boolean
 */
extern bool probability(double p);

#endif //FREE_PROJECT_UTILS_MATH_H
