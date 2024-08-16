#include "color.h"
#include <SDL2/SDL_render.h>
#include "rtweekend.h"

byte_colors color_to_bytes(const Color &color) {
    uint8_t rbyte = uint8_t(255.999 * color.x());
    uint8_t gbyte = uint8_t(255.999 * color.y());
    uint8_t bbyte = uint8_t(255.999 * color.z());
    byte_colors byte_color(rbyte, gbyte, bbyte);
    return byte_color;
}
