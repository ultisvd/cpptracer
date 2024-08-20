#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <glm/common.hpp>
#include <glm/vec3.hpp>
#include <limits>
#include <memory>
#include <vector>
#include "hittable.h"
#include "sphere.h"

using std::make_shared;
using std::shared_ptr;
using std::vector;

class Hittable_list {
   public:
    vector<Sphere> objects;

    Hittable_list() {}

    void clear() { objects.clear(); }

    void add(Sphere object) { objects.push_back(object); }

    [[nodiscard]]
    Hit_record hit(my_Ray &ray) const {
        int closestSphere = -1;
        fpoint distance = std::numeric_limits<float>::max();
        for (size_t i = 0; i < objects.size(); i++) {
            const Sphere &sphere = objects[i];
            glm::vec3 origin = ray.orig - sphere.center;

            fpoint a = glm::dot(ray.dir, ray.dir);
            fpoint b = 2.0f * glm::dot(origin, ray.dir);
            fpoint c = glm::dot(origin, origin) - sphere.radius * sphere.radius;

            fpoint discriminant = b * b - 4.0f * a * c;
            if (discriminant < 0.0f)
                continue;

            fpoint closestT = (-b - glm::sqrt(discriminant) / (2.0f * a));
            if (closestT > 0.0f && closestT < distance) {
                distance = closestT;
                closestSphere = (int)i;
            }
        }

        if (closestSphere < 0) {
            return Miss();
        }

        return ClosestHit(ray, distance, closestSphere);
    };

    Hit_record ClosestHit(const my_Ray &ray, fpoint distance, int index) const {
        Hit_record rec;
        rec.distance = distance;
        rec.index = index;

        const Sphere &closestSphere = objects[(size_t)index];

        glm::vec3 origin = ray.orig - closestSphere.center;
        rec.hitPoint = origin + ray.dir * distance;
        rec.normal = glm::normalize(rec.hitPoint);
        rec.hitPoint += closestSphere.center;

        return rec;
    }

    Hit_record Miss() const {
        Hit_record rec;
        rec.distance = -1.0f;
        return rec;
    }
};

#endif  // !HITTABLE_LIST_H
