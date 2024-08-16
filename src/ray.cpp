#include "ray.h"

point3 Ray::at(fpoint t) const {
    return orig + t * dir;
}

const point3 &Ray::origin() const {
    return orig;
}
const vec3 &Ray::direction() const {
    return dir;
}
