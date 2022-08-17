#ifndef RAY_H
#define RAY_H

#include "vec3.h"

typedef struct ray_s {
    vec3 origin;
    vec3 direction;
} ray;

vec3 ray_at(ray from, double t);

#endif