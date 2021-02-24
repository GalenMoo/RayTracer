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

    // for (int a = -11; a < 11; a++) {
    //     for (int b = -11; b < 11; b++) {
    //         auto choose_mat = random_double();
    //         Point center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

    //         if ((center - Point(4, 0.2, 0)).length() > 0.9) {
    //             std::shared_ptr<Material> sphere_material;

    //             if (choose_mat < 0.8) {
    //                 // diffuse
    //                 auto albedo = Color::random() * Color::random();
    //                 sphere_material = std::make_shared<Lambertian>(albedo);
    //                 world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
    //             } else if (choose_mat < 0.95) {
    //                 // metal
    //                 auto albedo = Color::random(0.5, 1);
    //                 auto fuzz = random_double(0, 0.5);
    //                 sphere_material = std::make_shared<Metal>(albedo, fuzz);
    //                 world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
    //             } else {
    //                 // glass
    //                 sphere_material = std::make_shared<Dielectric>(1.5);
    //                 world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
    //             }
    //         }
    //     }
    // }

    // auto material1 = std::make_shared<Dielectric>(1.5);
    // world.add(std::make_shared<Sphere>(Point(0, 1, 0), 1.0, material1));

    // auto material2 = std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    // world.add(std::make_shared<Sphere>(Point(-4, 1, 0), 1.0, material2));

    // auto material3 = std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    // world.add(std::make_shared<Sphere>(Point(4, 1, 0), 1.0, material3));

    return world;
}

Color testF(int i){
    std::cout << i;
    return Color(0,0,0);
}
// void testF(int i);

void Render(){

    //Image
    // const auto aspect_ratio = 16.0 / 9.0;
    // const int image_width = 400;
    // const int image_height = static_cast<int>(image_width / aspect_ratio);
    // const int samples_per_pixel = 100;
    // const int max_depth = 50;
    const auto aspect_ratio = 3.0 / 2.0;
    const int image_width = 1200;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;
    const int max_depth = 50;

    //World Setup
    Hittable_List world = random_scene();

    // // auto material_ground = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    // // auto material_center = std::make_shared<Lambertian>(Color(0.7, 0.3, 0.3));
    // // auto material_left   = std::make_shared<Metal>(Color(0.8, 0.8, 0.8), 0.3);
    // // world.add(std::make_shared<Sphere>(Point( 0.0, -100.5, -1.0), 100.0, material_ground));
    // // world.add(std::make_shared<Sphere>(Point( 0.0,    0.0, -1.0),   0.5, material_center));
    // // world.add(std::make_shared<Sphere>(Point(-1.0,    0.0, -1.0),   0.5, material_left));
    // // world.add(std::make_shared<Sphere>(Point( 1.0,    0.0, -1.0),   0.5, material_right));

    //1
    // auto material_ground = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    // auto material_center = std::make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
    // auto material_left   = std::make_shared<Dielectric>(1.5);
    // auto material_right  = std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 0.0);

    // world.add(std::make_shared<Sphere>(Point( 0.0, -100.5, -1.0), 100.0, material_ground));
    // world.add(std::make_shared<Sphere>(Point( 0.0,    0.0, -1.0),   0.5, material_center));
    // world.add(std::make_shared<Sphere>(Point(-1.0,    0.0, -1.0),   0.5, material_left));
    // world.add(std::make_shared<Sphere>(Point(-1.0,    0.0, -1.0),  -0.4, material_left));
    // world.add(std::make_shared<Sphere>(Point( 1.0,    0.0, -1.0),   0.5, material_right));

    // auto R = cos(PI/4);
    // Hittable_List world;

    // auto material_left  = std::make_shared<Lambertian>(Color(0,0,1));
    // auto material_right = std::make_shared<Lambertian>(Color(1,0,0));

    // world.add(std::make_shared<Sphere>(Point(-R, 0, -1), R, material_left));
    // world.add(std::make_shared<Sphere>(Point( R, 0, -1), R, material_right));


    // Camera
    // Point lookfrom(3,3,2);
    // Point lookat(0,0,-1);
    // Point vup(0,1,0);
    // auto dist_to_focus = (lookfrom-lookat).length();
    // auto aperture = 2.0;
    Point lookfrom(13,2,3);
    Point lookat(0,0,0);
    Point vup(0,1,0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.1;

    Camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);
    
    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    auto startTime = std::chrono::steady_clock::now();
    std::vector<std::thread> threadpool;
    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << " " << std::flush;
        for (int i = 0; i < image_width; ++i){
            Color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s){
                auto u = (i + random_double()) / (image_width-1);
                auto v = (j + random_double()) / (image_height-1);
                Ray r = cam.get_ray(u, v);
                threadpool.emplace_back(std::thread(ray_color, r, world, max_depth));
                // pixel_color += ray_color(r, world, max_depth);
            }
            for (auto &t : threadpool){
                t.join();
            }
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }
    std::cerr << "Finished!\n";

    auto endTime = std::chrono::steady_clock::now();
    std::cerr << "Time to complete: " << std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count() << "s\n";
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