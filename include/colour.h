#ifndef COLOUR_H
#define COLOUR_H

#include <stdio.h>
#include "vec3.h"

// Definition for colour type is in vec3

// Print the colour of the given pixel to FILE (default: stdout)
void colour_print(FILE* stream, vec3 pixel, int samples_per_pixel);

#endif