#ifndef HITTABLE_H
#define HITTABLE_H

#include "vec3.h"
#include "ray.h"
#include "material.h"

#define HR_ZERO_INIT {{0,0,0},{0,0,0},0,NULL,0}

struct material;
typedef struct material material;

typedef struct hit_record {
    vec3 p;
    vec3 normal;
    double t;
    material* mat_ptr;
    bool front_face;
} hit_record;

void hit_record_set_face_normal(hit_record* rec, ray* r, vec3* outward_normal) {
    rec->front_face = vec3_dot(&r->direction, outward_normal) < 0;
    rec->normal = rec->front_face ? *outward_normal : vec3_negate_r(*outward_normal);
}

#endif