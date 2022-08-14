#ifndef VEC3_H
#define VEC3_H

#include <math.h>
#include <stdio.h>
#include "rtweekend.h"

#define VEC3_ZERO_INIT {0.0, 0.0, 0.0}

typedef struct {
    double x;
    double y;
    double z;
} vec3, colour;

void vec3_negate(vec3* vector) {
    vector->x *= -1;
    vector->y *= -1;
    vector->z *= -1;
}

void vec3_add_v(vec3* vector, vec3* input) {
    vector->x += input->x;
    vector->y += input->y;
    vector->z += input->z;
}

void vec3_mul_s(vec3* vector, double scalar) {
    vector->x *= scalar;
    vector->y *= scalar;
    vector->z *= scalar;
}

void vec3_div_s(vec3* vector, double scalar) {
    vector->x /= scalar;
    vector->y /= scalar;
    vector->z /= scalar;
}

double vec3_square_length(vec3 vector) {
    return vector.x*vector.x + vector.y*vector.y + vector.z*vector.z;
}

double vec3_length(vec3 vector) {
    return sqrt(vec3_square_length(vector));
}

void vec3_print(FILE* stream, vec3 vector) {
    fprintf(stream, "%lf %lf %lf", vector.x, vector.y, vector.z);
}

void vec3_sub_v(vec3* vector, vec3* input) {
    vector->x -= input->x;
    vector->y -= input->y;
    vector->z -= input->z;
}

void vec3_mul_v(vec3* vector, vec3* input) {
    vector->x *= input->x;
    vector->y *= input->y;
    vector->z *= input->z;
}

void vec3_div_v(vec3* vector, vec3* input) {
    vector->x /= input->x;
    vector->y /= input->y;
    vector->z /= input->z;
}

double vec3_dot(vec3* vector, vec3* input) {
    return vector->x*input->x + vector->y*input->y + vector->z*input->z;
}

vec3 vec3_negate_r(vec3 vector) {
    vec3 output = vector;
    vec3_negate(&output);
    return output;
}

vec3 vec3_sub_v_r(vec3 vector, vec3 input) {
    vec3 output = vector;
    vec3_sub_v(&output, &input);
    return output;
}

vec3 vec3_add_v_r(vec3 vector, vec3 input) {
    vec3 output = vector;
    vec3_add_v(&output, &input);
    return output;
}

vec3 vec3_mul_v_r(vec3 vector, vec3 input) {
    vec3 output = vector;
    vec3_mul_v(&output, &input);
    return output;
}

vec3 vec3_mul_s_r(vec3 vector, double input) {
    vec3 output = vector;
    vec3_mul_s(&output, input);
    return output;
}

vec3 vec3_div_s_r(vec3 vector, double input) {
    vec3 output = vector;
    vec3_div_s(&output, input);
    return output;
}

vec3 vec3_cross(vec3 vector, vec3 input) {
    vec3 product = {vector.y * input.z - vector.z * input.y,
                    vector.z * input.x - vector.x * input.z,
                    vector.x * input.y - vector.y * input.x};
    return product;
}

vec3 vec3_unit(vec3 vector) {
    double denominator = vec3_length(vector);
    vec3 unit = vec3_div_s_r(vector, denominator);
    return unit;
}

vec3 vec3_random() {
    vec3 rand_vec = (vec3) {random_double(), random_double(), random_double()};
    return rand_vec;
}

vec3 vec3_random_i(double min, double max) { 
    vec3 rand_vec = (vec3) {random_double_i(min,max),random_double_i(min,max),random_double_i(min,max)};
    return rand_vec;
}

vec3 vec3_random_unit_sphere() {
    while (true) {
        vec3 p = vec3_random_i(-1,1);
        if (vec3_square_length(p) >= 1) continue;
        return p;
    }
}

vec3 vec3_random_unit_vector() {
    return vec3_unit(vec3_random_unit_sphere());
}

vec3 vec3_random_hemisphere(vec3* normal) {
    vec3 in_unit_sphere = vec3_random_unit_sphere();
    if (vec3_dot(&in_unit_sphere, normal) > 0.0)
        return in_unit_sphere;
    else {
        vec3_negate(&in_unit_sphere);
        return in_unit_sphere;
    }
}

vec3 vec3_random_unit_disk() {
    while (true) {
        vec3 p = (vec3) {random_double_i(-1,1), random_double_i(-1,1), 0};
        if (vec3_square_length(p) >= 1) {
            continue;
        }
        return p;
    }
}

bool vec3_near_zero(vec3* v) {
    double s = 1e-8;
    return (fabs(v->x) < s) && (fabs(v->y) < s) && (fabs(v->z) < s); 
}

vec3 vec3_reflect(vec3* v, vec3* n) {
    return vec3_sub_v_r(*v, vec3_mul_s_r(*n, vec3_dot(v,n)*2.0));
}

vec3 vec3_refract(vec3* uv, vec3* n, double etai_over_etat) {
    vec3 temp = vec3_negate_r(*uv);
    double cos_theta = fmin(vec3_dot(&temp, n), 1.0);
    vec3 r_out_perp = vec3_mul_s_r(vec3_add_v_r(vec3_mul_s_r(*n, cos_theta), *uv), etai_over_etat);
    vec3 r_out_parallel = vec3_mul_s_r(*n ,-sqrt(fabs(1.0 - vec3_square_length(r_out_perp))));
    return vec3_add_v_r(r_out_perp, r_out_parallel);
}

#endif