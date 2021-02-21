/*
 * @File: utility.cpp
 * @Author: Galen
 * @File Created: 2021-02-20 5:27:22 pm
 * @Last Modified: 2021-02-20 5:27:47 pm
 * @Description: 
 */
#include <cmath>

#include "point.h"
#include "ray.h"
#include "utility.h"

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

void write_color(std::ostream &out, Color c){
    out << static_cast<int>(255.999 * c[0]) << " "
        << static_cast<int>(255.999 * c[1]) << " "
        << static_cast<int>(255.999 * c[2]) << "\n";
}

Color ray_color(const Ray& r) {
    auto t = hit_sphere(Point(0,0,-1), 0.5, r);
    if (t > 0.0) {
        Point N = unit_vector(r.at(t) - Point(0,0,-1));
        // std::cerr << N << std::endl;
        return 0.5*Color(N.x()+1, N.y()+1, N.z()+1);
    }

    Point udir = unit_vector(r.dir());
    t = 0.5*(udir.y() + 1.0);
    return Color(1.0, 1.0, 1.0)*(1.0-t) + Color(0.5, 0.7, 1.0)*t;
}

double hit_sphere(const Point& center, double radius, const Ray& r) {
    Point oc = r.origin() - center;     //p-c
    auto a = dot(r.dir(), r.dir());     //r•r
    auto b = 2.0 * dot(oc, r.dir());    //2*((p-c)•r)
    auto c = dot(oc, oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;

    if (discriminant < 0)
        return -1.0;
    else
        return (-b - std::sqrt(discriminant) ) / (2.0*a);
}