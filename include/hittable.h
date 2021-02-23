#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
#include "mathutil.h"

struct hit_item{
    Point p;
    Point normal;
    double t;

    bool front_face;
    void set_face_normal(const Ray& r, const Point& outward_normal) {
        front_face = dot(r.dir(), outward_normal) < 0;
        normal = front_face ? outward_normal :-outward_normal;
    }
};

class Hittable {
    public:
        virtual bool hit(const Ray& r, double t_min, double t_max, hit_item& rec) const = 0;
};

#endif