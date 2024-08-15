#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <SDL2/SDL_render.h>
#include <vector>

using Color = vec3;

void write_color(SDL_Texture &texture, const Color &pixel_color);


#endif // !COLOR_H
