#ifndef UTIL_MATH_H
#define UTIL_MATH_H

#include "../master.h"

#include <math.h>

// TODO: Replace linmath.h, get rid of our own defines as possible

#define PI 3.14159265358979323846
#define DEG2RAD(degrees) ((PI / 180.0) * (degrees))
#define RAD2DEG(radians) ((180.0 / PI) * (radians))

static inline double clamp(double val, double min, double max) {
    return fmax(min, fmin(max, val));
}

static inline float clampf(float val, float min, float max) {
    return fmaxf(min, fminf(max, val));
}

#endif /* UTIL_MATH_H */
