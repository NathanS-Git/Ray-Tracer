#ifndef COLOUR_H
#define COLOUR_H

#include "vec3.h"
#include "rtweekend.h"
#include <stdio.h>

void colour_print(FILE* stream, vec3 pixel, int samples_per_pixel) {
    double r = pixel.x;
    double g = pixel.y;
    double b = pixel.z;

    // Divide the colour by the number of samples and gamma-correct for gamma=2.0
    double scale = 1.0 / samples_per_pixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);
    
    fprintf(stream, "%d %d %d\n", (int)(clamp(r,0,0.999)*255.0), (int)(clamp(g,0,0.999)*255.0), (int)(clamp(b,0,0.999)*255.0));
}

#endif