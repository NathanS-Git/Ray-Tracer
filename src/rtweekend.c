#include <math.h>
#include <stdlib.h>
#include "rtweekend.h"

double degrees_to_radians(double degrees) {
    return degrees * M_PI / 180.0;
}

double random_double() {
    return (double)rand() / (RAND_MAX + 1.0);
}

double random_double_i(double min, double max ) {
    return min + (max-min)*random_double();
}

double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}