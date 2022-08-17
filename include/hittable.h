#ifndef HITTABLE_H
#define HITTABLE_H

#include <stdbool.h>
#include "vec3.h"
#include "ray.h"

#define HR_ZERO_INIT {{0,0,0},{0,0,0},0,NULL,0}

typedef struct material_s material; // Forward declaration of material.h

typedef struct hit_record_s {
    vec3 p;
    vec3 normal;
    double t;
    material* mat_ptr;
    bool front_face;
} hit_record;


void hit_record_set_face_normal(hit_record* rec, ray* r, vec3* outward_normal);

#endif