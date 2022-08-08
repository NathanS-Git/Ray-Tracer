#ifndef MATERIAL_H
#define MATERIAL_H

#include "rtweekend.h"
#include "ray.h"
#include "hittable.h"

#define LAMBERTIAN 1
#define METAL 2
#define DIELECTRIC 3

#define MATERIAL_ZERO_INIT {0, {0, 0, 0}, 0, 0}

typedef struct material {
    int mat_type;
    colour a;
    double f;
    double ir;
} material;

bool lambertian_scatter(material* lambertian, ray* r_in, hit_record* rec, colour* attenuation, ray* scattered) {
    vec3 scatter_direction = vec3_add_v_r(rec->normal, vec3_random_unit_vector());
   
    if (vec3_near_zero(&scatter_direction)) {
        scatter_direction = rec->normal;
    }

    *scattered = (ray){rec->p, scatter_direction};
    *attenuation = lambertian->a;
    return true;
}

bool metal_scatter(material* metal, ray* r_in, hit_record* rec, colour* attenuation, ray* scattered) {
    vec3 temp = vec3_unit(r_in->direction);
    vec3 reflected = vec3_reflect(&temp, &rec->normal);
    *scattered = (ray){rec->p, vec3_add_v_r(vec3_mul_s_r(vec3_random_unit_sphere(), metal->f), reflected)};
    *attenuation = metal->a;
    return (vec3_dot(&scattered->direction, &rec->normal) > 0);
}

double reflectance(double cosine, double ref_idx) {
    double r0 = (1-ref_idx) / (1+ref_idx);
    r0 = r0*r0;
    return r0 + (1-r0)*pow((1-cosine), 5);
}

bool dielectric_scatter(material* dielectric, ray* r_in, hit_record* rec, colour* attenuation, ray* scattered) {
    *attenuation = (vec3){1.0, 1.0, 1.0};
    double refraction_ratio = rec->front_face ? (1.0/dielectric->ir) : dielectric->ir;
    vec3 unit_direction = vec3_unit(r_in->direction);
    vec3 temp_neg = vec3_negate_r(unit_direction);
    double cos_theta = fmin(vec3_dot(&temp_neg, &rec->normal), 1.0);
    double sin_theta = sqrt(1.0 - cos_theta*cos_theta);

    bool cannot_refract = refraction_ratio * sin_theta > 1.0;
    vec3 direction;

    if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double()) {
        direction = vec3_reflect(&unit_direction, &rec->normal);
    } else {
        direction = vec3_refract(&unit_direction, &rec->normal, refraction_ratio);
    }

    *scattered = (ray) {rec->p, direction};
    return true;
}



#endif
