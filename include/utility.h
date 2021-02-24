#ifndef UTILITY_H
#define UTILITY_H

#include "point.h"
#include "ray.h"
#include "sphere.h"
#include "camera.h"

#include "mathutil.h"

#include "hittable.h"
#include "hittable_list.h"

#include "materials.h"

void write_color(std::ostream &out, Color c);
void write_color(std::ostream &out, Color pixel_color, int samples_per_pixel);
Color ray_color(const Ray& r, Hittable& world, int depth);
double hit_sphere(const Point& center, double radius, const Ray& r);
/*
struct Color{
    double r{0};
    double g{0};
    double b{0};
};
*/

#endif