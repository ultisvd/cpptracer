#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include <limits>
#include <random>
#include <glm/vec3.hpp>
#include <tuple>

const float infinity = std::numeric_limits<float>::infinity();
const float pi = 3.1415926535897932385f;

using color_bytes = std::tuple<uint8_t, uint8_t, uint8_t>;

inline color_bytes color_to_bytes(const glm::vec3 &color) {
    uint8_t rbyte = uint8_t(255.99 * color.r);
    uint8_t gbyte = uint8_t(255.99 * color.g);
    uint8_t bbyte = uint8_t(255.99 * color.b);
    color_bytes bytes(rbyte, gbyte, bbyte);
    return bytes;
}









#endif  // !DECLARATIONS_H
