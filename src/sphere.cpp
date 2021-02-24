/*
 * @File: sphere.cpp
 * @Author: Galen
 * @File Created: 2021-02-21 3:37:41 pm
 * @Last Modified: 2021-02-21 4:13:27 pm
 * @Description: 
 */
#include <cmath>

#include "point.h"
#include "sphere.h"
#include "hittable.h"

bool Sphere::hit(const Ray& r, double t_min, double t_max, hit_item& rec) const{
    Point oc = r.origin() - center_;
    auto a = r.dir().length_squared();
    auto half_b = dot(oc, r.dir());
    auto c = oc.length_squared() - radius_*radius_;

    auto discriminant = half_b*half_b - a*c;
    if (discriminant < 0) return false;
    auto sqrtd = std::sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    rec.normal = (rec.p - center_) / radius_;
    Point outward_normal = (rec.p - center_) / radius_;
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_;

    return true;
}
