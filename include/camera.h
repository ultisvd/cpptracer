#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"
#include "hittable_list.h"
#include "rtweekend.h"
#include "vec3.h"
#include <array>

class Camera {
  public:
    int image_width = 300;
    fpoint aspect_ratio = 16.0 / 9.0;
    int samples_per_pixel = 32;
    int max_depth = 10;

    void render(const Hittable_list &world) {
        init();
        vector<vec3> colors;
        colors.reserve(40000000);

        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
        for (int y = 0; y < image_height; y++) {
            for (int x = 0; x < image_width; x += 8) {
                for (int i = 0; i < 8; i++) {
                    Color pixel_color(0, 0, 0);
                    for (int sample = 0; sample < samples_per_pixel; sample++) {
                        Ray ray = get_ray(x+i, y);
                        pixel_color += ray_color(ray, max_depth, world);
                    }
                    write_color(colors, pixel_color * pixel_samples_scale);
                }
            }
        }
        std::clog << "\rDone                                \n";
        for (auto &color : colors) {
            std::cout << int(color.e[0]) << ' ' << int(color.e[1]) << ' '
                      << int(color.e[2]) << '\n';
        }
    }

  private:
    int image_height;
    fpoint vfov = 120;
    double pixel_samples_scale;
    point3 center;
    point3 first_pixel;
    vec3 pixel_delta_u;
    vec3 pixel_delta_v;

    void init() {
        image_height = int(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        center = point3(0, 0, 0);
        fpoint focal_length = 1.0;
        fpoint theta = degrees_to_radians(vfov);
        fpoint h = std::tan(theta / 2);
        fpoint viewport_height = 2 * h * focal_length;
        fpoint viewport_width =
            viewport_height * (fpoint(image_width) / image_height);

        vec3 viewport_u = vec3(viewport_width, 0, 0);
        vec3 viewport_v = vec3(0, -viewport_height, 0);
        pixel_samples_scale = 1.0 / samples_per_pixel;

        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        vec3 viewport_upleft =
            center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
        first_pixel = viewport_upleft + 0.5 * (pixel_delta_u + pixel_delta_v);
    }

    vec3 sample_square() const {
        return vec3(random_fpoint() - 0.5, random_fpoint() - 0.5, 0);
    }

    Ray get_ray(int x, int y) const {
        auto offset = sample_square();
        auto pixel_sample = first_pixel + ((x + offset.x()) * pixel_delta_u) +
                            ((y + offset.y()) * pixel_delta_v);
        auto ray_origin = center;
        auto ray_direction = pixel_sample - ray_origin;
        return Ray(ray_origin, ray_direction);
    }

    Color ray_color(const Ray &ray, int depth,
                    const Hittable_list &world) const {
        if (depth <= 0) {
            return Color(0, 0, 0);
        }
        Hit_record rec;
        if (world.hit(ray, Interval(0.001, infinity), rec)) {
            vec3 direction = random_on_hemisphere(rec.normal);
            return 0.5 * ray_color(Ray(rec.p, direction), depth - 1, world);
        }

        vec3 unit_dir = normalize(ray.direction());
        fpoint a = 0.5 * (unit_dir.y() + 1.0);
        return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
    }
};

#endif // !CAMERA_H
