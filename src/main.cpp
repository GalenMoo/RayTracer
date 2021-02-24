#include <iostream>
#include <thread>
#include <memory>
#include <chrono>
#include <vector>

#include "utility.h"
#include "materials.h"

void Render();
Hittable_List random_scene();
Color ray_color(const Ray& r, Hittable& world, int depth);


//global
Color pixel_color(0, 0, 0);

int main(){
    Render();

    // Point p = Point(4, 5, 6);
    // Point p1 = Point(1, 7, 4);
    // std::cout << p-p1;
    // p[0] = 12;


    return EXIT_SUCCESS;
}

Hittable_List random_scene() {
    Hittable_List world;

    auto ground_material = std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    world.add(std::make_shared<Sphere>(Point(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            Point center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - Point(4, 0.2, 0)).length() > 0.9) {
                std::shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = Color::random() * Color::random();
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = Color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = std::make_shared<Dielectric>(1.5);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<Dielectric>(1.5);
    world.add(std::make_shared<Sphere>(Point(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    world.add(std::make_shared<Sphere>(Point(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_shared<Sphere>(Point(4, 1, 0), 1.0, material3));

    return world;
}

void Render(){

    //Image
    const auto aspect_ratio = 3.0 / 2.0;
    const int image_width = 1200;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 50;
    const int max_depth = 50;

    //World Setup
    Hittable_List world = random_scene();

    // //1
    // auto material_ground = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    // auto material_center = std::make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
    // auto material_left   = std::make_shared<Dielectric>(1.5);
    // auto material_right  = std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 0.0);

    // world.add(std::make_shared<Sphere>(Point( 0.0, -100.5, -1.0), 100.0, material_ground));
    // world.add(std::make_shared<Sphere>(Point( 0.0,    0.0, -1.0),   0.5, material_center));
    // world.add(std::make_shared<Sphere>(Point(-1.0,    0.0, -1.0),   0.5, material_left));
    // world.add(std::make_shared<Sphere>(Point(-1.0,    0.0, -1.0),  -0.4, material_left));
    // world.add(std::make_shared<Sphere>(Point( 1.0,    0.0, -1.0),   0.5, material_right));

    // Camera
    Point lookfrom(13,2,3);
    Point lookat(0,0,0);
    Point vup(0,1,0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.1;

    Camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);
    
    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    auto startTime = std::chrono::steady_clock::now();
    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << " " << std::flush;
        for (int i = 0; i < image_width; ++i){
            Color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s){
                auto u = (i + random_double()) / (image_width-1);
                auto v = (j + random_double()) / (image_height-1);
                Ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }

    std::cerr << "Finished!\n";
    auto endTime = std::chrono::steady_clock::now();
    std::cerr << "Time to complete: " << std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count() << "s\n";
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