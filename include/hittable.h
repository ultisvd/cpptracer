#ifndef HITTABLE_H
#define HITTABLE_H

#include <glm/common.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/geometric.hpp>
#include "declarations.h"

class Hit_record {
   public:
    float distance;
    glm::vec3 hitPoint;
    glm::vec3 normal;
    size_t index;
};


#endif  // !HITTABLE_H
