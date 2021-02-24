#ifndef CAMERA_H
#define CAMERA_H

#include "point.h"
#include "ray.h"

class Camera{
    public:
        Camera(Point lookfrom, Point lookat, Point vup, 
                double vfov, double aspect_ratio,
                double aperture, double focus_dist);

        Ray get_ray(double u, double v) const;

    private:
        Point origin_;
        Point lower_left_corner_;
        Point horizontal_;
        Point vertical_;
        Point u_, v_, w_;
        double lens_radius_;
};

#endif