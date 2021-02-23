#ifndef MATHUTIL_H
#define MATHUTIL_H

#include "point.h"

// Constants
const double MYINFINITY = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;

double dot(const Point p1, const Point p2);
Point cross(const Point p1, const Point p2);
Point unit_vector(Point p);
double degrees_to_radians(double degrees);

double clamp(double x, double min, double max);

double random_double();
double random_double(double min, double max);

#endif