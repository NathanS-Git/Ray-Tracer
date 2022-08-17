#ifndef SPHERE_H
#define SPHERE_H

#define SPHERE_ZERO_INIT {VEC3_ZERO_INIT, 0.0}

#include <stdbool.h>
#include "vec3.h"
#include "ray.h"
#include "hittable.h"
#include "material.h"

typedef struct sphere_s {
    vec3 center;
    double r;
    material* mat_ptr;
} sphere;


// Check if the given ray hits the given sphere
bool sphere_hit(sphere* s, ray* r, double t_min, double t_max, hit_record* rec);

#endif