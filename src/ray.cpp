#include "ray.h"

point3 my_Ray::at(fpoint t) const {
    return orig + t * dir;
}

const point3 &my_Ray::origin() const {
    return orig;
}
const vec3 &my_Ray::direction() const {
    return dir;
}
