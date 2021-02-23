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
#include "hittable.h"
#include "utility.h"

void write_color(std::ostream &out, Color c){
    out << static_cast<int>(255.999 * c[0]) << " "
        << static_cast<int>(255.999 * c[1]) << " "
        << static_cast<int>(255.999 * c[2]) << "\n";
}

void write_color(std::ostream &out, Color pixel_color, int samples_per_pixel){
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Divide the color by the number of samples and gamma-correct for gamma=2.0.
    auto scale = 1.0 / samples_per_pixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}

Color ray_color(const Ray& r, Hittable& world, int depth) {
    hit_item rec;
    if (depth <= 0)
        return Color(0,0,0);

    if (world.hit(r, 0.001, MYINFINITY, rec)){
        Point target = rec.p + rec.normal + random_unit_vector();
        return 0.5 * ray_color(Ray(rec.p, target - rec.p), world, depth-1);
    }

    Point udir = unit_vector(r.dir());
    auto t = 0.5*(udir.y() + 1.0);
    return Color(1.0, 1.0, 1.0)*(1.0-t) + Color(0.5, 0.7, 1.0)*t;
}

double hit_sphere(const Point& center, double radius, const Ray& r) {
    Point oc = r.origin() - center;     //p-c
    auto a = r.dir().length_squared();
    auto half_b = dot(oc, r.dir());
    auto c = oc.length_squared() - radius*radius;
    auto discriminant = half_b*half_b - a*c;

    if (discriminant < 0)
        return -1.0;
    else
        return (-half_b - std::sqrt(discriminant) ) / a;
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