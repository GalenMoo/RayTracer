#ifndef RAY_H
#define RAY_H

#include "point.h"

class Ray
{
    public:
        Ray(const Point o, const Point d) : origin_(o), dir_(d) {}

        Point origin() const { return origin_; }
        Point dir() const { return dir_; }
        Point at(double t) const;
    private:
        Point origin_;
        Point dir_;
};

#endif