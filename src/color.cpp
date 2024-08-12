#include "color.h"
#include "rtweekend.h"

void write_color(vector<vec3>& out, const Color &pixel_color) {
    auto r = pixel_color.e[0];
    auto g = pixel_color.e[1];
    auto b = pixel_color.e[2];

    // translate to [0, 1]
    int rbyte = int(255.999 * r);
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);

    out.push_back(vec3(rbyte,gbyte,bbyte));
}
