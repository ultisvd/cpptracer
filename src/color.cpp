#include "color.h"
#include "rtweekend.h"
#include <SDL2/SDL_render.h>

void write_color(SDL_Texture &texture, const Color &pixel_color, int x, int y) {
    auto r = pixel_color.e[0];
    auto g = pixel_color.e[1];
    auto b = pixel_color.e[2];
    uint8_t rbyte = uint8_t(255.999 * r);
    uint8_t gbyte = uint8_t(255.999 * g);
    uint8_t bbyte = uint8_t(255.999 * b);
    void *pixels;
    int pitch;

    SDL_LockTexture(&texture, NULL, &pixels, &pitch);

    // int colorbytes = 0;
    // colorbytes |= rbyte << 24;
    // colorbytes |= gbyte << 16;
    // colorbytes |= bbyte << 8;

    // out.push_back(colorbytes);
}
