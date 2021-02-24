/*
 * @File: mathutil.cpp
 * @Author: Galen
 * @File Created: 2021-02-21 6:47:52 pm
 * @Last Modified: 2021-02-21 6:48:07 pm
 * @Description: 
 */
#include <cmath>
#include <limits>
#include <memory>

#include "point.h"
#include "mathutil.h"

Point reflect(const Point& v, const Point& n){
    return v - 2*dot(v,n)*n;
}

Point refract(const Point& uv, const Point& n, double etai_over_etat){
    auto cos_theta = fmin(dot(-uv, n), 1.0);
    Point r_out_perp =  etai_over_etat * (uv + cos_theta*n);
    Point r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}

double dot(const Point p1, const Point p2){
    return p1[0] * p2[0] +
           p1[1] * p2[1] +
           p1[2] * p2[2];
}

Point cross(const Point p1, const Point p2){
    return Point(p1[1] * p2[2] - p1[2] * p2[1],
                 p1[2] * p2[0] - p1[0] * p2[2],
                 p1[0] * p2[1] - p1[1] * p2[0]);
}

Point unit_vector(Point p){
    return p/p.length();
}

double degrees_to_radians(double degrees){
    return degrees * PI / 180.0;
}

double clamp(double x, double min, double max){
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

double random_double(){
    // Returns a random real in [0,1).
    return rand() / (RAND_MAX + 1.0);
}

double random_double(double min, double max){
    // Returns a random real in [min,max).
    return min + (max-min)*random_double();
}

Point random_in_unit_sphere(){
    while (true){
        auto p = Point::random(-1,1);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

Point random_unit_vector(){
    return unit_vector(random_in_unit_sphere());
}

Point random_in_unit_disk(){
    while (true) {
        auto p = Point(random_double(-1,1), random_double(-1,1), 0);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}