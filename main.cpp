#include "include/color.h"
#include <iostream>

struct Image {
    int image_width;
    int image_height;

    Image(int w, int h) : image_width(w), image_height(h) {}
};

int main(int argc, char *argv[]) {
    // if (argc != 1 ) {
    //     std::cout << "Hello, " << argv[1] << '!' << '\n';
    // } else {
    //     std::cout << "Hello, world!" << '\n';
    // }

    Image img(1280, 720);

    auto image_width = img.image_width;
    auto image_height = img.image_height;

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for (int y = 0; y < image_height; y++) {
        std::clog << "\rScanlines remaining: " << (image_height - y) << ' '
                  << std::flush;

        for (int x = 0; x < image_width; x++) {
            // red increases to the right
            // green increases to the bottom
            auto color = Color(fpoint(x) / (image_width - 1),
                               fpoint(y) / (image_height - 1), 0);
            write_color(std::cout, color);
        }
    }
    std::clog << "\rDone                                \n";

    return 0;
}
