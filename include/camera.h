#ifndef CAMERA_H
#define CAMERA_H

#include "point.h"
#include "ray.h"

class Camera{
    public:
        Camera();
        Ray get_ray(double u, double v) const;

    private:
        Point origin_;
        Point lower_left_corner_;
        Point horizontal_;
        Point vertical_;
};

#endif