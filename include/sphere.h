#ifndef SPHERE_H
#define SPHERE_H

#include <glm/ext/vector_float3.hpp>
#include "declarations.h"
class Sphere {

   public:
    glm::vec3 center;
    glm::vec3 color;
    float radius;
    float roughness;
    Sphere(const glm::vec3 &center, float radius, glm::vec3 color, float roughness)
        : center(center), color(color), radius(std::fmax(0.f, radius)), roughness(roughness) {}
};


#endif  // !SPHERE_H
