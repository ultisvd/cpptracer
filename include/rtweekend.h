#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <random>
#include <vector>

#include "declarations.h"
#include "interval.h"
#include "ray.h"
#include "rng.h"

// C++ Std Usings

using std::make_shared;
using std::shared_ptr;
using std::vector;

// Constants

// Utility Functions

inline fpoint degrees_to_radians(fpoint degrees) {
    return degrees * pi / 180.0f;
}


#endif
