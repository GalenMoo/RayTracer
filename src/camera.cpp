/*
 * @File: camera.cpp
 * @Author: Galen
 * @File Created: 2021-02-22 7:59:24 pm
 * @Last Modified: 2021-02-22 7:59:26 pm
 * @Description: 
 */

#include "camera.h"

Camera::Camera(){
    auto aspect_ratio = 16.0 / 9.0;
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    origin_ = Point(0, 0, 0);
    horizontal_ = Point(viewport_width, 0.0, 0.0);
    vertical_ = Point(0.0, viewport_height, 0.0);
    lower_left_corner_ = origin_ - horizontal_/2 - vertical_/2 - Point(0, 0, focal_length);
    
}

Ray Camera::get_ray(double u, double v) const{
    return Ray(origin_, lower_left_corner_ + u*horizontal_ + v*vertical_ - origin_);
}