#include <iostream>

#include "point.h"
#include "ray.h"
#include "utility.h"

void Render();

int main(){
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = Point(0, 0, 0);
    auto horizontal = Point(viewport_width, 0, 0);
    auto vertical = Point(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - Point(0, 0, focal_length);

    auto u = double(5) / (image_width-1);
    auto v = double(10) / (image_height-1);

    Ray r(origin, lower_left_corner + horizontal*u + vertical*v - origin);

    // r.at(5);
    // std::cout << std::endl;
    // r.at(2);
    // std::cout << std::endl;
    // r.at(1);
    // std::cout << std::endl;
    // r.at(4);
    // std::cout << std::endl;

    // std::cout << r.at(3);
    // std::cout << std::endl;
    // std::cout << r.at(3) - Point(0,0,-1);
    // std::cout << std::endl;
    // std::cout << (r.at(3) - Point(0,0,-1)).length();
    // std::cout << std::endl;
    // std::cout << unit_vector(r.at(3) - Point(0,0,-1));
    Render();

    // Point p = Point(4, 5, 6);
    // Point p1 = Point(1, 7, 4);
    // std::cout << p-p1;
    // p[0] = 12;


    return EXIT_SUCCESS;
}


void Render(){
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // Camera

    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = Point(0, 0, 0);
    auto horizontal = Point(viewport_width, 0, 0);
    auto vertical = Point(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - Point(0, 0, focal_length);

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        //TODO add progress bar with /b
        std::cerr << "\rScanlines remaining: " << j << " " << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto u = double(i) / (image_width-1);
            auto v = double(j) / (image_height-1);
            Ray r(origin, lower_left_corner + horizontal*u + vertical*v - origin);
            Color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "Finished!\n";
}