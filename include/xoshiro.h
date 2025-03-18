#ifndef XOSHIRO_H
#define XOSHIRO_H

#include <random>

static uint64_t rng_seed = std::random_device{}();

inline uint64_t rng_next() {
    return (rng_seed += rng_seed * rng_seed | 5) >> 32;
}

/* This is xoshiro256+ 1.0, our best and fastest generator for floating-point
   numbers. We suggest to use its upper bits for floating-point
   generation, as it is slightly faster than xoshiro256++/xoshiro256**. It
   passes all tests we are aware of except for the lowest three bits,
   which might fail linearity tests (and just those), so if low linear
   complexity is not considered an issue (as it is usually the case) it
   can be used to generate 64-bit outputs, too.

   We suggest to use a sign test to extract a random Boolean value, and
   right shifts to extract subsets of bits.

   The state must be seeded so that it is not everywhere zero. If you have
   a 64-bit seed, we suggest to seed a splitmix64 generator and use its
   output to fill s. */

/*  Written in 2018 by David Blackman and Sebastiano Vigna (vigna@acm.org)

To the extent possible under law, the author has dedicated all copyright
and related and neighboring rights to this software to the public domain
worldwide.

Permission to use, copy, modify, and/or distribute this software for any
purpose with or without fee is hereby granted.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR
IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE. */

#include <stdint.h>

static inline uint64_t rotl(const uint64_t x, int k) {
    return (x << k) | (x >> (64 - k));
}
static uint64_t xoshiro_seed[4] = {
    std::random_device{}(),
    std::random_device{}(),
    std::random_device{}(),
    std::random_device{}(),
};

inline uint64_t xoshiro_next(void) {
    const uint64_t result = xoshiro_seed[0] + xoshiro_seed[3];

    const uint64_t t = xoshiro_seed[1] << 17;

    xoshiro_seed[2] ^= xoshiro_seed[0];
    xoshiro_seed[3] ^= xoshiro_seed[1];
    xoshiro_seed[1] ^= xoshiro_seed[2];
    xoshiro_seed[0] ^= xoshiro_seed[3];

    xoshiro_seed[2] ^= t;

    xoshiro_seed[3] = rotl(xoshiro_seed[3], 45);

    return result;
}


#endif
