#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <iostream>

using Color = vec3;

void write_color(std::ostream& out, const Color& pixel_color);

#endif // !COLOR_H
