#include "ray.h"

vec3 ray_at(ray from, double t) {
    vec3 output = vec3_add_v_r(from.origin, vec3_mul_s_r(from.direction, t));
    return output;
}
