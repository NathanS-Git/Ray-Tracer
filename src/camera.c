#include <math.h>
#include "utils.h"
#include "camera.h"

camera cam_init(vec3 lookfrom, vec3 lookat, vec3 vup, double vfov, double aspect_ratio, double aperture, double focus_dist) {
    camera cam;
    cam.theta = degrees_to_radians(vfov);
    cam.h = tan(cam.theta/2);
    cam.viewport_height = 2.0 * cam.h;
    cam.viewport_width = aspect_ratio * cam.viewport_height;

    cam.w = vec3_unit(vec3_sub_v_r(lookfrom, lookat));
    cam.u = vec3_unit(vec3_cross(vup, cam.w));
    cam.v = vec3_cross(cam.w, cam.u);

    cam.origin = lookfrom;
    cam.horizontal = vec3_mul_s_r(vec3_mul_s_r(cam.u, cam.viewport_width), focus_dist);
    cam.vertical = vec3_mul_s_r(vec3_mul_s_r(cam.v, cam.viewport_height), focus_dist);
    cam.lower_left_corner = vec3_sub_v_r(vec3_sub_v_r(vec3_sub_v_r(cam.origin, vec3_div_s_r(cam.horizontal, 2)), vec3_div_s_r(cam.vertical, 2)), vec3_mul_s_r(cam.w, focus_dist));

    cam.lens_radius = aperture / 2.0;

    return cam;
}

ray camera_get_ray(camera* c, double s, double t) {
    vec3 rd = vec3_mul_s_r(vec3_random_unit_disk(), c->lens_radius);
    vec3 offset = vec3_add_v_r(vec3_mul_s_r(c->u, rd.x), vec3_mul_s_r(c->v, rd.y));

    vec3 ray_origin = vec3_add_v_r(c->origin, offset);
    vec3 ray_direction = vec3_sub_v_r(vec3_sub_v_r(vec3_add_v_r(vec3_add_v_r(c->lower_left_corner, vec3_mul_s_r(c->horizontal, s)), vec3_mul_s_r(c->vertical, t)), c->origin), offset);
    ray r = {ray_origin, ray_direction};
    return r;
}