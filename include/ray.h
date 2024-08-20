#ifndef RAY_H
#define RAY_H

#include <glm/ext/vector_float3.hpp>
#include "declarations.h"
class my_Ray {
   public:
    my_Ray() {}
    glm::vec3 orig;
    glm::vec3 dir;
    my_Ray(const glm::vec3 &origin, const glm::vec3 &direction)
        : orig(origin), dir(direction) {}


    glm::vec3 const at(float t) const;
};

#endif  // !RAY_H
