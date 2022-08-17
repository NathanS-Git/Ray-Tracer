#include <stdlib.h>
#include "hittable_list.h"

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
            *rec = *temp_rec;
        }
        head = head->next_node;
    }
    free(temp_rec);
    return hit_anything;
}