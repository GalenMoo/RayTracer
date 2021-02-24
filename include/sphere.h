#ifndef SPHERE_H
#define SPHERE_H

#include <memory>

#include "point.h"
#include "hittable.h"
#include "materials.h"

class Sphere : public Hittable{
    public:
        Sphere() {}
        Sphere(Point c, double r, std::shared_ptr<Material> m) : center_(c), radius_(r), mat_(m) {};

        virtual bool hit(
            const Ray& r, double t_min, double t_max, hit_item& rec) const override;
        
        Point center_;
        double radius_;
        std::shared_ptr<Material> mat_;
};

#endif