#include <iostream>
#include <memory>

#include "utility.h"

void Render();

int main(){
    Render();

    // Point p = Point(4, 5, 6);
    // Point p1 = Point(1, 7, 4);
    // std::cout << p-p1;
    // p[0] = 12;


    return EXIT_SUCCESS;
}


void Render(){

    //Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;
    const int max_depth = 50;

    // World
    Hittable_List world;
    world.add(std::make_shared<Sphere>(Point(0,0,-1), 0.5));
    world.add(std::make_shared<Sphere>(Point(0,-100.5,-1), 100));

    // Camera
    Camera cam;

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        //TODO add progress bar with /b
        std::cerr << "\rScanlines remaining: " << j << " " << std::flush;
        for (int i = 0; i < image_width; ++i) {
            Color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (i + random_double()) / (image_width-1);
                auto v = (j + random_double()) / (image_height-1);
                Ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }

            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }

    std::cerr << "Finished!\n";
}