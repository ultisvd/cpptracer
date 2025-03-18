#ifndef RNG_H
#define RNG_H

#include <climits>
#include <cstdlib>
#include <iostream>
#include "xoshiro.h"
#include "declarations.h"



// inline float random_float(uint32_t &state) {
//     state = state * 747796405 + 2891336453;
//     uint64_t result = ((state >> ((state >> 28) + 4)) ^ state) * 277803737;
//     result = (result >> 22) ^ result;
//     return (float)result / std::numeric_limits<uint64_t>::max();
// }
//     
//
inline float random_float_old() {
    uint64_t num = xoshiro_next();
    float fl = (float)num / std::numeric_limits<uint64_t>::max();
    return fl;
}

// inline float random_float(uint32_t state, float min, float max) {
//     auto rand_num = random_float(state);
//     return min + (max - min) * rand_num;
// }

#endif
