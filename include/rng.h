#ifndef RNG_H
#define RNG_H

#include <climits>
#include <cstdlib>
#include "xoshiro.h"
#include "declarations.h"

inline float random_float() {
    uint64_t num = xoshiro_next();
    return (float)num / (float)(RAND_MAX);
}

inline float random_float(float min, float max) {
    auto rand_num = random_float();
    return min + (max - min) * rand_num;
}



#endif
