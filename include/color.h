#ifndef COLOR_H
#define COLOR_H

#include <SDL2/SDL_render.h>
#include <tuple>
#include "declarations.h"
#include "vec3.h"

using Color = vec3;
using byte_colors = std::tuple<uint8_t, uint8_t, uint8_t>;

byte_colors color_to_bytes(const Color &color);

#endif  // !COLOR_H
