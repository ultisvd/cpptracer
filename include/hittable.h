#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
#include <optional>

class Hit_record {
public:
    point3 p;
    fpoint t;
    vec3 normal;
    bool front_face;
    void set_face_normal(const Ray& r, const vec3& outward_normal) {
        //outward_normal is normalized
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class Hittable {
public: 
    virtual ~Hittable() = default;
    virtual std::optional<Hit_record> hit(const Ray& r, fpoint ray_tmin, fpoint ray_tmax) const = 0;
};

#endif // !HITTABLE_H
