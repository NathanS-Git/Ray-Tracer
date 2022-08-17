#include <math.h>
#include "sphere.h"

bool sphere_hit(sphere* s, ray* r, double t_min, double t_max, hit_record* rec) {
    vec3 oc = vec3_sub_v_r(r->origin, s->center);
    double a = vec3_square_length(r->direction);
    double half_b = vec3_dot(&oc, &r->direction);
    double c = vec3_square_length(oc) - s->r*s->r;
    double discriminant =  half_b*half_b - a*c;
    if (discriminant < 0) return false;
    double sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    double root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    rec->t = root;
    rec->p = ray_at(*r, rec->t);
    rec->normal = vec3_mul_s_r(vec3_sub_v_r(rec->p, s->center), s->r);
    vec3 outward_normal = vec3_div_s_r(vec3_sub_v_r(rec->p, s->center), s->r);
    hit_record_set_face_normal(rec, r, &outward_normal);
    rec->mat_ptr = s->mat_ptr;

    return true;
}
