#ifndef RAY_H
#define RAY_H

#include "vec3.h"

typedef struct ray {
    vec3 origin;
    vec3 direction;
} ray;

vec3 ray_at(ray from, double t) {
    vec3 output = vec3_add_v_r(from.origin, vec3_mul_s_r(from.direction, t));
    return output;
}

#endif