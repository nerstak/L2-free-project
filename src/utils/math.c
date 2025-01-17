#include <stdlib.h>
#include "math.h"

extern int max(int x, int y) {
    return (x >= y) ? x: y;
}

extern double maxDouble(double x, double y) {
    // Maybe that wrong, i know comparing double is unsafe, but i'm done
    // https://stackoverflow.com/questions/15374444/floating-point-how-much-can-i-trust-less-than-greater-than-comparisons

    if (x > y) {
        return x;
    } else if (x < y) {
        return y;
    } else {
        return x;
    }
}

extern int min(int x, int y) {
    return (x <= y) ? x: y;
}

extern int sign(double x) {
    if(x<0)
        return -1;
    else
        return 1;
}

extern bool probability(double p) {
    return (rand() / (RAND_MAX + 1.0)) < p;
}