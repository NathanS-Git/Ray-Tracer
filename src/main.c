#include <stdio.h>
#include <stdbool.h>
#include "camera.h"
#include "vec3.h" 
#include "colour.h"
#include "material.h"
#include "hittable_list.h"
#include "ray.h"
#include "sphere.h"

colour ray_colour(ray* r, hittable_list* world, int depth) {
    hit_record rec = (hit_record)HR_ZERO_INIT;
    rec.mat_ptr = &(material)MATERIAL_ZERO_INIT;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0) {
        return (vec3) {0,0,0};
    }

    if (hl_hit(world, r, 0.001, INFINITY, &rec)) {
        ray scattered;
        colour attenuation;
        switch (rec.mat_ptr->mat_type) {
            case 0:
                return (colour){0,0,0};
            case LAMBERTIAN:
                if (lambertian_scatter(rec.mat_ptr, r, &rec, &attenuation, &scattered)) {
                    return vec3_mul_v_r(attenuation, ray_colour(&scattered, world, depth-1));
                }
            case METAL:
                if (metal_scatter(rec.mat_ptr, r, &rec, &attenuation, &scattered)) {
                    return vec3_mul_v_r(attenuation, ray_colour(&scattered, world, depth-1));
                }
            case DIELECTRIC:
                if (dielectric_scatter(rec.mat_ptr, r, &rec, &attenuation, &scattered)) {
                    return vec3_mul_v_r(attenuation, ray_colour(&scattered, world, depth-1));
                }
            default:
                return (colour){0,0,0};
                
        }
        //vec3 target = vec3_add_v_r(vec3_add_v_r(rec.normal, vec3_random_unit_vector()), rec.p);
        vec3 target = vec3_add_v_r(rec.p, vec3_random_hemisphere(&rec.normal));
        ray input = {rec.p,vec3_sub_v_r(target, rec.p)};
        return vec3_mul_s_r( ray_colour(&input, world, depth-1), 0.5);
    }
    vec3 unit_direction = vec3_unit(r->direction);
    double t = 0.5*(unit_direction.y + 1.0);
    vec3 output = vec3_add_v_r(vec3_mul_s_r((vec3) {1.0, 1.0, 1.0}, (1.0-t)), vec3_mul_s_r((vec3){0.5, 0.7,1.0}, t));
    
    return output;
}

hittable_list* random_scene() {
    hittable_list* world = (hittable_list*)malloc(sizeof(hittable_list));

    material* ground_material = (material*)malloc(sizeof(material));
    *ground_material = (material){LAMBERTIAN, {0.5, 0.5, 0.5}};
    sphere* ground = (sphere*)malloc(sizeof(sphere));
    *ground = (sphere){{0, -1000, 0}, 1000, ground_material};
    world->object = ground;

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            double choose_mat = random_double();
            vec3 center = {a + 0.9*random_double(), 0.2, b + 0.9*random_double()};

            material* sphere_material = (material*)malloc(sizeof(material));
            sphere* sphere_object = (sphere*)malloc(sizeof(sphere));
            if (vec3_length(vec3_sub_v_r(center, (vec3) {4, 0.2, 0})) > 0.9) {
                if (choose_mat < 0.8) {
                    // diffuse (lambertian)
                    vec3 albedo = vec3_mul_v_r(vec3_random(), vec3_random());
                    *sphere_material = (material){LAMBERTIAN, albedo};
                    *sphere_object = (sphere){center, 0.2, sphere_material};
                    world = hl_add(world, sphere_object); 
                } else if (choose_mat < 0.95) {
                    // metal
                    vec3 albedo = vec3_random_i(0.5, 1);
                    double fuzz = random_double(0, 0.5);
                    *sphere_material = (material){METAL, albedo, fuzz};
                    *sphere_object = (sphere){center, 0.2, sphere_material};
                    world = hl_add(world, sphere_object);
                } else {
                    // glass (dielectric)
                    *sphere_material = (material){DIELECTRIC, {0,0,0}, 0, 1.5};
                    *sphere_object = (sphere){center, 0.2, sphere_material};
                    world = hl_add(world, sphere_object);
                }
            }
        }
    }  

    material* material1 = (material*)malloc(sizeof(material));
    sphere* sphere1 = (sphere*)malloc(sizeof(sphere));
    *material1 = (material){DIELECTRIC, {0,0,0}, 0, 1.5};
    *sphere1 = (sphere){(vec3){0,1,0}, 1.0, material1};
    world = hl_add(world, sphere1);

    material* material2 = (material*)malloc(sizeof(material));
    sphere* sphere2 = (sphere*)malloc(sizeof(sphere));
    *material2 = (material){LAMBERTIAN, {0.4,0.2,0.1}};
    *sphere2 = (sphere){(vec3){-4,1,0}, 1.0, material2};
    world = hl_add(world, sphere2);

    material* material3 = (material*)malloc(sizeof(material));
    sphere* sphere3 = (sphere*)malloc(sizeof(sphere));
    *material3 = (material){METAL, {0.7,0.6,0.5}, 0.0};
    *sphere3 = (sphere){(vec3){4,1,0}, 1.0, material3};
    world = hl_add(world, sphere3);

    return world;
}

int main() {
    
    // Image
    const double aspect_ratio = 3.0 / 2.0;
    const int image_width = 1200;
    const int image_height = image_width / aspect_ratio;
    const int samples_per_pixel = 500;
    const int max_depth = 50;

    // World
    /*
    hittable_list* world = &(hittable_list)HL_ZERO_INIT;
    material material_ground = {LAMBERTIAN, {0.8, 0.8, 0.0}};
    material material_center = {LAMBERTIAN, {0.1, 0.2, 0.5}};
    material material_left = {DIELECTRIC, {0.0, 0.0, 0.0}, 0, 1.5};
    material material_right = {METAL, {0.8, 0.6, 0.2}, 0.0};

    world->object = &(sphere){{0,-100.5,-1.0}, 100.0, &material_ground};
    world = hl_add(world, &(sphere){{0,0,-1}, 0.5, &material_center});
    world = hl_add(world, &(sphere){{-1,0,-1}, 0.5, &material_left});
    world = hl_add(world, &(sphere){{-1,0,-1}, -0.45, &material_left});
    world = hl_add(world, &(sphere){{1,0,-1}, 0.5, &material_right});*/
    hittable_list* world = random_scene();

    // Camera
    vec3 lookfrom = {13,2,3};
    vec3 lookat = {0,0,0};
    vec3 vup = {0,1,0};
    double dist_to_focus = 10.0;
    double aperture = 0.1;
    camera cam = cam_init(lookfrom, lookat, vup, 20.0, aspect_ratio, aperture, dist_to_focus);

    // Render
    printf("P3\n%d %d\n255\n",image_width,image_height);

    for (int j = image_height-1; j >= 0; --j) {
        fprintf(stderr, "\rScanlines remaining: %3d", j);
        for (int i = 0; i < image_width; ++i) {
            colour pixel_colour = (vec3) {0,0,0};
            for (int s = 0; s < samples_per_pixel; ++s) {
                double rand1 = random_double();
                double rand2 = random_double();
                double u =  ((double)i+rand1) / (image_width-1);
                double v =  ((double)j+rand2) / (image_height-1);
                ray r = camera_get_ray(&cam, u, v);
                pixel_colour = vec3_add_v_r(pixel_colour, ray_colour(&r, world, max_depth));
            }
            
            colour_print(stdout, pixel_colour, samples_per_pixel);
        }

    }
    fprintf(stderr, "\nDone\n");

    return 0;
}
