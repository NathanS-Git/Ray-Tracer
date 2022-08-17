#ifndef MATERIAL_H
#define MATERIAL_H

#include <stdbool.h>
#include "vec3.h"
#include "ray.h"
#include "hittable.h"

#define MATERIAL_ZERO_INIT {0, {0, 0, 0}, 0, 0}

enum material_type {LAMBERTIAN, METAL, DIELECTRIC};

typedef struct material_s {
    enum material_type mat_type;
    colour a;
    double f;
    double ir;
} material;

// Scatter light on a lambertian surface
bool lambertian_scatter(material* lambertian, ray* r_in, hit_record* rec, colour* attenuation, ray* scattered);

// Scatter light on a metal surface
bool metal_scatter(material* metal, ray* r_in, hit_record* rec, colour* attenuation, ray* scattered);

double reflectance(double cosine, double ref_idx);

// Scatter light dependant on a dielectric material
bool dielectric_scatter(material* dielectric, ray* r_in, hit_record* rec, colour* attenuation, ray* scattered);


#endif