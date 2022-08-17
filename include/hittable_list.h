#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <stdbool.h>
#include "sphere.h"
#include "ray.h"
#include "hittable.h"

#define HL_ZERO_INIT {NULL, NULL, 0}

// Linked list to store all the objects in the scene
typedef struct hittable_list_s {
    sphere* object;
    struct hittable_list_s* next_node;
} hittable_list;

// Add an object to the hittable list
hittable_list* hl_add(hittable_list* list, sphere* object);

// Check every object within the list for a hit
bool hl_hit(hittable_list* list, ray* r, double t_min, double t_max, hit_record* rec);

#endif