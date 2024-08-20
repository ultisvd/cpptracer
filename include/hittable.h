#ifndef HITTABLE_H
#define HITTABLE_H

#include "interval.h"
#include "ray.h"
#include <glm/common.hpp>
#include <glm/geometric.hpp>

class Hit_record {
   public:
    fpoint distance;
    glm::vec3 hitPoint;
    glm::vec3 normal;
    int index;
};


#endif  // !HITTABLE_H
