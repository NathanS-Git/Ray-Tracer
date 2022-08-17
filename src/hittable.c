#include "hittable.h"

void hit_record_set_face_normal(hit_record* rec, ray* r, vec3* outward_normal) {
    rec->front_face = vec3_dot(&r->direction, outward_normal) < 0;
    rec->normal = rec->front_face ? *outward_normal : vec3_negate_r(*outward_normal);
}