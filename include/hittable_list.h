#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <cstdint>
#include <glm/common.hpp>
#include <glm/vec3.hpp>
#include <limits>
#include "ray.h"
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
        size_t sphereIdx = UINT32_MAX;
        float distance = std::numeric_limits<float>::max();
        for (size_t i = 0; i < objects.size(); i++) {
            const Sphere &sphere = objects[i];
            glm::vec3 origin = ray.orig - sphere.center;

            float a = glm::dot(ray.dir, ray.dir);
            float b = 2.0f * glm::dot(origin, ray.dir);
            float c = glm::dot(origin, origin) - sphere.radius * sphere.radius;

            float discriminant = b * b - 4.0f * a * c;
            if (discriminant < 0.0f)
                continue;

            float closestHit = (-b - glm::sqrt(discriminant)) / (2.0f * a);
            if (closestHit > 0.0f && closestHit < distance) {
                distance = closestHit;
                sphereIdx = i;
            }
        }

        if (sphereIdx == UINT32_MAX) {
            return Miss();
        }

        return ClosestHit(ray, distance, sphereIdx);
    };

    Hit_record ClosestHit(const my_Ray &ray, float distance, size_t index) const {
        Hit_record rec;
        rec.distance = distance;
        rec.index = index;

        const Sphere &closestSphere = objects[(size_t)index];

        glm::vec3 origin = ray.orig - closestSphere.center;
        rec.hitPoint = origin + ray.dir * distance;
        rec.normal = glm::normalize((rec.hitPoint));
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
