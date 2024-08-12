#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <array>
#include <vector>

using Color = vec3;

void write_color(std::vector<vec3> &out, const Color &pixel_color);


#endif // !COLOR_H
