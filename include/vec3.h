#ifndef VEC3_H
#define VEC3_H

#include <stdbool.h>
#include <stdio.h>

#define VEC3_ZERO_INIT {{0.0}, {0.0}, {0.0}}

typedef struct vec3_s {
    double x;
    double y;
    double z;
} vec3, colour;

// Negates a given vector
void vec3_negate(vec3* vector);
// Add's a scalar to each component of a given vector
void vec3_add_v(vec3* vector, vec3* input);
// Multiply each component of a vector by a scalar
void vec3_mul_s(vec3* vector, double scalar);
// Divide each component of a vector by a scalar
void vec3_div_s(vec3* vector, double scalar);
// Print the contents of a vector to a given output stream
void vec3_print(FILE* stream, vec3 vector);
// Subtract two vectors. The result is put into the first vector
void vec3_sub_v(vec3* vector, vec3* input);
// Multiply two vectors. The result is put into the first vector
void vec3_mul_v(vec3* vector, vec3* input);
// Divide two vectors. The result is put into the first vector
void vec3_div_v(vec3* vector, vec3* input);
// Return the squared length of the vector
double vec3_square_length(vec3 vector);
// Return the length of the vector
double vec3_length(vec3 vector);
// Return the dot product of two vectors
double vec3_dot(vec3* vector, vec3* input);

// Returns the negated given vector
vec3 vec3_negate_r(vec3 vector);
// Returns the subtraction of the two given vectors
vec3 vec3_sub_v_r(vec3 vector, vec3 input);
// Returns the addition of the two given vectors
vec3 vec3_add_v_r(vec3 vector, vec3 input);
// Returns the multiplication of the two given vectors
vec3 vec3_mul_v_r(vec3 vector, vec3 input);
// Returns the product of the given vector with the scalar
vec3 vec3_mul_s_r(vec3 vector, double input);
// Returns the division of the given vector with the scalar
vec3 vec3_div_s_r(vec3 vector, double input);
// Returns the cross product of the two given vectors
vec3 vec3_cross(vec3 vector, vec3 input);
// Returns the given vectors unit vector
vec3 vec3_unit(vec3 vector);
// Returns a vector where each coordinate is a random value from 0 to 1
vec3 vec3_random();
// Returns a vector where each coordinate is a random value from min to max
vec3 vec3_random_i(double min, double max);
// Returns a vector pointing in a random direction in a unit-sphere
vec3 vec3_random_unit_sphere();
// Returns the unit vector of a random direction in a unit-sphere
vec3 vec3_random_unit_vector();
// Return a vector in a random direciton in a hemisphere centered at the given normal vector
vec3 vec3_random_hemisphere(vec3* normal);
// Return a vector in a random unit disk
vec3 vec3_random_unit_disk();

// Return true if a vector is near zero
bool vec3_near_zero(vec3* v);

// Returns a reflected vector
vec3 vec3_reflect(vec3* v, vec3* n);
// Returns a refracted vector
vec3 vec3_refract(vec3* uv, vec3* n, double etai_over_etat);

#endif