#include "ray.h"

glm::vec3 const my_Ray::at(float t) const {
    return orig + t * dir;
}

