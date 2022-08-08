#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <stdlib.h>
#include "hittable.h"
#include "sphere.h"
#include "ray.h"

#define HL_ZERO_INIT {NULL, NULL, 0}

typedef struct hittable_list {
    sphere* object;
    struct hittable_list* next_node;
    unsigned int size;
} hittable_list;

hittable_list* hl_add(hittable_list* list, sphere* object) {
    hittable_list* new_list = (hittable_list*)malloc(sizeof(hittable_list));
    new_list->object = object;
    new_list->next_node = list;
    return new_list;
}

bool hl_hit(hittable_list* list, ray* r, double t_min, double t_max, hit_record* rec) {
    hittable_list* head = list;
    hit_record* temp_rec = (hit_record*)malloc(sizeof(hit_record));
    *temp_rec = (hit_record)HR_ZERO_INIT;
    bool hit_anything = false;
    double closest_so_far = t_max;
    while (head != NULL) {
        if (sphere_hit(head->object, r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec->t;
            
            /*rec->p = temp_rec->p;
            rec->normal = temp_rec->normal
            rec->t = temp_rec->t;
            rec->front_face = temp_rec->front_face;*/
            *rec = *temp_rec;
        }
        head = head->next_node;
    }
    free(temp_rec);
    return hit_anything;
}

#endif