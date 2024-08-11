#include "color.h"
#include "ray.h"
#include "vec3.h"
#include <iostream>

struct Image {
    int image_width;
    int image_height;
    fpoint aspect_ratio;

    Image(int w, fpoint aspect_ratio = 16.0 / 9.0)
        : image_width(w), image_height(int(w / aspect_ratio)),
          aspect_ratio(aspect_ratio) {}
};

fpoint hit_sphere(const point3 &center, fpoint radius, const Ray &r) {
    vec3 oc = center - r.origin();
    auto a = r.direction().length_squared();
    auto h = dot(r.direction(), oc);
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = h * h - a * c;
    if (discriminant < 0) {
        return -1.0;
    }
    return (h - std::sqrt(discriminant)) / (a);
}

Color ray_color(const Ray &r) {
    auto t = hit_sphere(point3(0, 0, -1), 0.5, r);
    if (t > 0.0) {
        vec3 N = normalize(r.at(t) - vec3(0,0,-1));
        return 0.5*Color(N.x()+1, N.y()+1, N.z()+1);
    }
    vec3 unit_dir = normalize(r.direction());
    fpoint a = 0.5 * (unit_dir.y() + 1.0);
    return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}

int main(int argc, char *argv[]) {

    Image img(1280);

    auto image_width = img.image_width;
    auto image_height = img.image_height;

    fpoint focal_length = 1.0;
    fpoint viewport_height = 2.0;
    fpoint viewport_width =
        viewport_height * (fpoint(image_width) / image_height);
    auto camera_center = point3(0, 0, 0);

    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    auto viewport_upleft = camera_center - vec3(0, 0, focal_length) -
                           viewport_u / 2 - viewport_v / 2;
    auto first_pixel_loc =
        viewport_upleft + 0.5 * (pixel_delta_u + pixel_delta_v);

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for (int y = 0; y < image_height; y++) {
        std::clog << "\rScanlines remaining: " << (image_height - y) << ' '
                  << std::flush;
        for (int x = 0; x < image_width; x++) {
            auto pixel_center =
                first_pixel_loc + (x * pixel_delta_u) + (y * pixel_delta_v);
            auto ray_dir = pixel_center - camera_center;
            Ray r(camera_center, ray_dir);
            Color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }
    std::clog << "\rDone                                \n";

    return 0;
}
