#ifndef SPHERE_H
#define SPHERE_H

#include "point.h"
#include "hittable.h"

class Sphere : public Hittable{
    public:
        Sphere() {}
        Sphere(Point c, double r) : center_(c), radius_(r) {};

        virtual bool hit(
            const Ray& r, double t_min, double t_max, hit_item& rec) const override;
        
        Point center_;
        double radius_;
};

#endif