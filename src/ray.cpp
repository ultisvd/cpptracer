#include "ray.h"

glm::vec3 const my_Ray::at(fpoint t) const {
    return orig + t * dir;
}

