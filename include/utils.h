#ifndef UTILS_H
#define UTILS_H

// Converts degrees to radians
double degrees_to_radians(double degrees);

// Returns a random number from 0 to 1
double random_double();

// Returns a random number from min to max
double random_double_i(double min, double max );

// Clamps a number x, between min and max
double clamp(double x, double min, double max);

#endif