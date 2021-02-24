#ifndef MATHUTIL_H
#define MATHUTIL_H

#include "point.h"

// Constants
const double MYINFINITY = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;

Point reflect(const Point& v, const Point& n);
Point refract(const Point& uv, const Point& n, double etai_over_etat);

double dot(const Point p1, const Point p2);
Point cross(const Point p1, const Point p2);
Point unit_vector(Point p);
double degrees_to_radians(double degrees);

double clamp(double x, double min, double max);

double random_double();
double random_double(double min, double max);
Point random_in_unit_sphere();
Point random_unit_vector();
Point random_in_unit_disk();

#endif