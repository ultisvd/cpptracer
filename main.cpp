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
    Image img(256, 256);
    std::cout << "P3\n" << img.image_width << ' ' << img.image_height << "\n255\n";

    for (int j = 0; j < img.image_height; j++) {
        for (int i = 0; i < img.image_width; i++) {
            auto r = double(i) / (img.image_width - 1);
            auto g = double(j) / (img.image_height - 1);
            auto b = 0.0;

            int ir = int(255.999 * r);
            int ig = int(255.999 * g);
            int ib = int(255.999 * b);

            std::cout << ir << ' ' << ig << ' '  << ib << '\n';
        }
    }



    return 0;
}
