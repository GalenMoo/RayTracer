#ifndef MATERIAL_H
#define MATERIAL_H

#include <cmath>

#include "mathutil.h"
#include "utility.h"

struct hit_item;

class Material{
    public:
        virtual bool scatter(
            const Ray& r_in, const hit_item& rec, Color& attenuation, Ray& scattered
        ) const = 0;
};

class Lambertian : public Material{
    public:
        Lambertian(const Color& a) : albedo_(a) {}

        virtual bool scatter(
            const Ray& r_in, const hit_item& rec, Color& attenuation, Ray& scattered
        ) const override{
            auto scatter_direction = rec.normal + random_unit_vector();

            if (scatter_direction.near_zero())
                scatter_direction = rec.normal;

            scattered = Ray(rec.p, scatter_direction);
            attenuation = albedo_;
            return true;
        }

    public:
        Color albedo_;
};

class Metal : public Material{
    public:
        Metal(const Color& a, double f) : albedo_(a), fuzz_(f < 1 ? f : 1) {}

        virtual bool scatter(
            const Ray& r_in, const hit_item& rec, Color& attenuation, Ray& scattered
        ) const override {
            Point reflected = reflect(unit_vector(r_in.dir()), rec.normal);
            scattered = Ray(rec.p, reflected + fuzz_*random_in_unit_sphere());

            attenuation = albedo_;
            return (dot(scattered.dir(), rec.normal) > 0);
        }

    public:
        Color albedo_;
        double fuzz_;
};

class Dielectric : public Material {
    public:
        Dielectric(double index_of_refraction) : ir_(index_of_refraction) {}

        virtual bool scatter(
            const Ray& r_in, const hit_item& rec, Color& attenuation, Ray& scattered
        ) const override {
            attenuation = Color(1.0, 1.0, 1.0);
            double refraction_ratio = rec.front_face ? (1.0/ir_) : ir_;

            Point unit_direction = unit_vector(r_in.dir());
            double cos_theta = std::fmin(dot(-unit_direction, rec.normal), 1.0);
            double sin_theta = std::sqrt(1.0 - cos_theta*cos_theta);

            bool cannot_refract = refraction_ratio * sin_theta > 1.0;
            Point direction;

            if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double())
                direction = reflect(unit_direction, rec.normal);
            else
                direction = refract(unit_direction, rec.normal, refraction_ratio);

            scattered = Ray(rec.p, direction);
            return true;
        }

        double ir_; // Index of Refraction

    private:
        static double reflectance(double cosine, double ref_idx) {
            // Use Schlick's approximation for reflectance.
            auto r0 = (1-ref_idx) / (1+ref_idx);
            r0 = r0*r0;
            return r0 + (1-r0)*pow((1 - cosine),5);
        }
};

#endif