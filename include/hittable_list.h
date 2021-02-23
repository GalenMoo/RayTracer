#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <memory>
#include <vector>

class Hittable_List : public Hittable {
    public:
        Hittable_List() {}
        Hittable_List(std::shared_ptr<Hittable> object) { add(object); }

        void clear() { objects.clear(); }
        void add(std::shared_ptr<Hittable> object) { objects.push_back(object); }

        virtual bool hit(
            const Ray& r, double t_min, double t_max, hit_item& rec) const override;

        std::vector<std::shared_ptr<Hittable>> objects;
};

#endif