#ifndef SPHERE_H
#define SPHERE_H

#include <glm/ext/vector_float3.hpp>
#include "hittable.h"

class Sphere {

   public:
    glm::vec3 center;
    fpoint radius;
    glm::vec3 color;
    Sphere(const glm::vec3 &center, fpoint radius, glm::vec3 color)
        : center(center), radius(std::fmax(0, radius)), color(color) {}
};


#endif  // !SPHERE_H
