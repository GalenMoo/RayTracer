/*
 * @File: hittable_list.cpp
 * @Author: Galen
 * @File Created: 2021-02-21 5:30:30 pm
 * @Last Modified: 2021-02-21 5:30:33 pm
 * @Description: 
 */
#include "ray.h"
#include "hittable_list.h"

bool Hittable_List::hit(const Ray& r, double t_min, double t_max, hit_item& rec) const {
    hit_item temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto& object : objects) {
        if (object->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}