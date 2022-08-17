#include <math.h>
#include "rtweekend.h"
#include "colour.h"

void colour_print(FILE* stream, colour pixel, int samples_per_pixel) {

    // Divide the colour by the number of samples and gamma-correct for gamma=2.0
    double scale = 1.0 / samples_per_pixel;
    double r = sqrt(scale * pixel.x);
    double g = sqrt(scale * pixel.y);
    double b = sqrt(scale * pixel.z);
    
    fprintf(stream, "%d %d %d\n", (int)(clamp(r,0,0.999)*255.0), (int)(clamp(g,0,0.999)*255.0), (int)(clamp(b,0,0.999)*255.0));
}