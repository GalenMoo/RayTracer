#ifndef UTILITY_H
#define UTILITY_H

#include "point.h"

double dot(const Point p1, const Point p2);
Point cross(const Point p1, const Point p2);
Point unit_vector(Point p);
void write_color(std::ostream &out, Color c);
Color ray_color(const Ray& r);
double hit_sphere(const Point& center, double radius, const Ray& r);

/*
struct Color{
    double r{0};
    double g{0};
    double b{0};
};
*/

#endif