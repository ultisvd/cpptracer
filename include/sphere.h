#ifndef SPHERE_H
#define SPHERE_H

#include <glm/ext/vector_float3.hpp>
#include "declarations.h"
class Sphere {
   public:
    glm::vec3 center;
    glm::vec3 color;
    glm::vec3 em_color;
    float em_str;
    float radius;
    Sphere(const glm::vec3 &center,
           glm::vec3 color,
           glm::vec3 em_color,
           float em_str,
           float radius)
        : center(center),
          color(color),
          em_color(em_color),
          em_str(em_str),
          radius(std::fmax(0.f, radius)) {}
};

#endif  // !SPHERE_H
