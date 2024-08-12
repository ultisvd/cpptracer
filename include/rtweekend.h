#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>
#include <random>
#include <vector>

#include "color.h"
#include "ray.h"
#include "vec3.h"
#include "declarations.h"
#include "interval.h"

// C++ Std Usings

using std::make_shared;
using std::shared_ptr;
using std::vector;

// Constants


// Utility Functions

inline fpoint degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline fpoint random_fpoint() {
    static std::minstd_rand gen(std::random_device{}());
    static std::uniform_real_distribution<fpoint> dist(0, 1);
    return dist(gen);
}

inline fpoint random_fpoint(fpoint min, fpoint max) {
    return min + (max - min) * random_fpoint();
}


#endif
