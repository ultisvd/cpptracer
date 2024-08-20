#ifndef RNG_H
#define RNG_H

#include <climits>
#include <cstdlib>
#include "xoshiro.h"
#include "declarations.h"

inline fpoint random_fpoint() {
    uint64_t num = xoshiro_next();
    return (float)num / (float)(RAND_MAX);
}

inline fpoint random_fpoint(fpoint min, fpoint max) {
    auto rand_num = random_fpoint();
    return min + (max - min) * rand_num;
}



#endif
