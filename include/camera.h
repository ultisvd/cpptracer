#ifndef CAMERA_H
#define CAMERA_H

#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <raylib.h>
#include <sys/types.h>
#include <cstdint>
#include "color.h"
#include "hittable.h"
#include "hittable_list.h"
#include "rtweekend.h"
#include "vec3.h"

struct pixel_buffer {
    vector<Col> pixels;
    int sample_amount;
    size_t width, height;
    void init(size_t width, size_t height) {
        pixels.reserve(width * height * sizeof(Col));
        for (size_t i = 0; i < pixels.capacity(); i++) {
            pixels.push_back(Col(0, 0, 0));
        }
    }
};

class TracingCamera {
   public:
    size_t image_width = 300;
    fpoint aspect_ratio = 16.0 / 9.0;
    int samples_per_pixel = 32;
    int max_depth = 10;
    pixel_buffer buffer;
    point3 lookfrom = point3(0, 0, 0);
    point3 lookat = point3(0, 0, -1);
    vec3 vup = vec3(0, 1, 0);

    size_t get_height() const { return image_height; }

    void render_frame(const Hittable_list &world, RenderTexture2D &texture) {
        if (buffer.sample_amount < 1) {
            buffer.sample_amount++;
            for (size_t y = 0; y < image_height; y++) {
                for (size_t x = 0; x < image_width; x++) {
                    Col p_col(0, 0, 0);
                    my_Ray ray = get_ray(x, y);
                    p_col = ray_color(ray, max_depth, world);
                    buffer.pixels[y * image_width + x] = p_col;
                }
            }
        } else {
            if (buffer.sample_amount < samples_per_pixel) {
                buffer.sample_amount++;
                for (size_t y = 0; y < image_height; y++) {
                    for (size_t x = 0; x < image_width; x++) {
                        Col p_col(0, 0, 0);
                        my_Ray ray = get_ray(x, y);
                        p_col = ray_color(ray, max_depth, world);
                        Col avg = buffer.pixels[y * image_width + x];
                        avg = avg - (avg / buffer.sample_amount);
                        avg += p_col / buffer.sample_amount;
                        buffer.pixels[y * image_width + x] = avg;
                    }
                }
            }
        }
        BeginTextureMode(texture);
        for (size_t row = 0; row < image_height; row++) {
            for (size_t col = 0; col < image_width; col++) {
                const auto [rbyte, gbyte, bbyte] =
                    color_to_bytes(buffer.pixels[image_width * row + col]);
                Color color{rbyte, gbyte, bbyte, 255};
                DrawPixel(col, row, color);
            }
        }
        EndTextureMode();

        // SDL_LockTexture(texture, NULL, &pixels_ptr, &pitch);
        // for (size_t row = 0; row < image_height; row++) {
        //     dst = (uint32_t *)((uint8_t *)pixels_ptr + row * (size_t)pitch);
        //     for (size_t col = 0; col < image_width; col++) {
        //         const auto [rbyte, gbyte, bbyte] =
        //             color_to_bytes(buffer.pixels[image_width * row + col]);
        //         if (buffer.sample_amount <= samples_per_pixel) {
        //         }
        //         *dst++ = SDL_MapRGBA(format, rbyte, gbyte, bbyte, 255);
        //     }
        // }
        // SDL_UnlockTexture(texture);
    }

    void init() {
        image_height = (size_t)((fpoint)image_width / (fpoint)aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;
        buffer.init(image_width, image_height);

        center = lookfrom;
        fpoint focal_length = (lookfrom - lookat).length();
        fpoint theta = degrees_to_radians(vfov);
        fpoint h = std::tan(theta / 2);
        fpoint viewport_height = 2 * h * focal_length;
        fpoint viewport_width =
            viewport_height * (fpoint(image_width) / (fpoint)image_height);

        w = normalize(lookfrom - lookat);
        u = normalize(cross(vup, w));
        v = cross(w, u);

        vec3 viewport_u = viewport_width * u;
        vec3 viewport_v = viewport_height * -v;
        pixel_samples_scale = 1.0 / samples_per_pixel;

        pixel_delta_u = viewport_u / (fpoint)image_width;
        pixel_delta_v = viewport_v / (fpoint)image_height;

        vec3 viewport_upleft =
            center - (focal_length * w) - viewport_u / 2 - viewport_v / 2;
        first_pixel = viewport_upleft + 0.5 * (pixel_delta_u + pixel_delta_v);
    }

   private:
    size_t image_height;
    fpoint vfov = 120;
    double pixel_samples_scale;
    point3 center;
    point3 first_pixel;
    vec3 pixel_delta_u;
    vec3 pixel_delta_v;
    vec3 u, v, w;

    vec3 sample_square() const {
        return vec3(random_fpoint() - 0.5, random_fpoint() - 0.5, 0);
    }

    my_Ray get_ray(size_t x, size_t y) const {
        auto offset = sample_square();
        auto pixel_sample = first_pixel +
                            (((fpoint)x + offset.x()) * pixel_delta_u) +
                            (((fpoint)y + offset.y()) * pixel_delta_v);
        auto ray_origin = center;
        auto ray_direction = pixel_sample - ray_origin;
        return my_Ray(ray_origin, ray_direction);
    }

    Col ray_color(const my_Ray &ray,
                  int depth,
                  const Hittable_list &world) const {
        if (depth <= 0) {
            return Col(0, 0, 0);
        }
        Hit_record rec;
        if (world.hit(ray, Interval(0.001, infinity), rec)) {
            vec3 direction = random_on_hemisphere(rec.normal);
            return 0.5 * ray_color(my_Ray(rec.p, direction), depth - 1, world);
        }

        vec3 unit_dir = normalize(ray.direction());
        fpoint a = 0.5 * (unit_dir.y() + 1.0);
        return (1.0 - a) * Col(1.0, 1.0, 1.0) + a * Col(0.5, 0.7, 1.0);
    }
};

#endif  // !CAMERA_H
