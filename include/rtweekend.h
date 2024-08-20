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
#include <glm/common.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/random.hpp>

// C++ Std Usings

using std::make_shared;
using std::shared_ptr;
using std::vector;

// Constants

// Utility Functions

inline float degrees_to_radians(float degrees) {
    return degrees * pi / 180.0f;
}


#endif
