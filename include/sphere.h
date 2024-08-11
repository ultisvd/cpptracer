#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
class Sphere : public Hittable {
private:
    point3 center;
    fpoint radius;
public: 
    Sphere(const point3& center, fpoint radius) : center(center), radius(std::fmax(0, radius)) {}
    
    std::optional<Hit_record> hit(const Ray& ray, fpoint ray_tmin, fpoint ray_tmax) const override {
        // find discriminant
        vec3 circle_origin = center - ray.origin();
        auto a = ray.direction().length_squared();
        auto h = dot(ray.direction(), circle_origin);
        auto c = dot(circle_origin, circle_origin) - radius * radius;
        auto discriminant = h * h - a * c;
        if (discriminant < 0) {
            return std::nullopt;
        }
        auto sqrtd = std::sqrt(discriminant);

        // find suitable root from the quadratic (h +- sqrt(discriminant) / a)
        auto root = (h - sqrtd) / a;
        if (root <= ray_tmin || root >= ray_tmax) {
            root = (h + sqrtd) / a;
            if (root <= ray_tmin || root >= ray_tmax){
                return std::nullopt;
            }
        }

        Hit_record rec {
            .p = ray.at(root),
            .t = root,
        };
        vec3 outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(ray, outward_normal);
        return rec;
    }
};

#endif // !SPHERE_H
