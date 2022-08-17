#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include "ray.h"

typedef struct camera_s {
    double theta;
    double h;
    double viewport_height;
    double viewport_width;

    double focal_length;
    vec3 w;
    vec3 u;
    vec3 v;

    vec3 origin;
    vec3 horizontal;
    vec3 vertical;
    vec3 lower_left_corner;

    double lens_radius;

} camera;

// Initialize a camera struct with the given attributes
camera cam_init(vec3 lookfrom, vec3 lookat, vec3 vup, double vfov, double aspect_ratio, double aperture, double focus_dist);


ray camera_get_ray(camera* c, double s, double t);

#endif