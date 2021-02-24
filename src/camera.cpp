/*
 * @File: camera.cpp
 * @Author: Galen
 * @File Created: 2021-02-22 7:59:24 pm
 * @Last Modified: 2021-02-22 7:59:26 pm
 * @Description: 
 */

#include "camera.h"
#include "mathutil.h"
#include <cmath>        // std::tan(double)

Camera::Camera(Point lookfrom, Point lookat, Point vup, 
                double vfov, double aspect_ratio,
                double aperture, double focus_dist){

    auto theta = degrees_to_radians(vfov);
    auto h = tan(theta/2);
    auto viewport_height = 2.0 * h;
    auto viewport_width = aspect_ratio * viewport_height;

    w_ = unit_vector(lookfrom - lookat);
    u_ = unit_vector(cross(vup, w_));
    v_ = cross(w_, u_);

    origin_ = lookfrom;
    horizontal_ = focus_dist * viewport_width * u_;
    vertical_ = focus_dist * viewport_height * v_;
    lower_left_corner_ = origin_ - horizontal_/2 - vertical_/2 - focus_dist*w_;

    lens_radius_ = aperture / 2;
}

Ray Camera::get_ray(double s, double t) const {
    return Ray(origin_, lower_left_corner_ + s*horizontal_ + t*vertical_ - origin_);
}