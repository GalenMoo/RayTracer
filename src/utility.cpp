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
        Ray scattered;
        Color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth-1);
        return Color(0,0,0);
    }

    Point udir = unit_vector(r.dir());
    auto t = 0.5*(udir.y() + 1.0);
    return Color(1.0, 1.0, 1.0)*(1.0-t) + Color(0.5, 0.7, 1.0)*t;
}