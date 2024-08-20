#ifndef CAMERA_H
#define CAMERA_H

#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <omp.h>
#include <raylib.h>
#include <sys/types.h>
#include <cstddef>
#include <cstdint>
#include <glm/common.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/random.hpp>
#include "hittable.h"
#include "hittable_list.h"
#include "rtweekend.h"

struct pixel_buffer {
    vector<glm::vec3> pixels;
    int sample_amount = 1;
    size_t width, height;
    void init(size_t width, size_t height) {
        pixels.reserve(width * height * sizeof(glm::vec3));
        for (size_t i = 0; i < pixels.capacity(); i++) {
            pixels.push_back(glm::vec3(0, 0, 0));
        }
    }
    glm::vec3 get_pixel(size_t index) {
        return pixels[index] / (float)sample_amount;
    }
    void reset() {
        pixels.clear();
        sample_amount = 0;
        for (size_t i = 0; i < pixels.capacity(); i++) {
            pixels.push_back(glm::vec3(0, 0, 0));
        }
    }
};

class TracingCamera {
   public:
    int image_width;
    fpoint aspect_ratio;
    int samples_per_pixel;
    int max_depth;
    pixel_buffer buffer;
    glm::vec3 lookfrom = glm::vec3(0, 0, 0);
    glm::vec3 lookat = glm::vec3(0, 0, -1);
    glm::vec3 vup = glm::vec3(0, 1, 0);
    std::vector<glm::vec3> rayDirections;

    vector<uint8_t> bytes;

    [[nodiscard]]
    int get_height() const {
        return image_height;
    }

    void calculate_pixels(pixel_buffer &buffer, const Hittable_list &world) {
        for (size_t y = 0; y < image_height; y++) {
            for (size_t x = 0; x < image_width; x++) {
                glm::vec3 p_col(0, 0, 0);
                p_col = ray_color(x, y, world);
                buffer.pixels[y * image_width + x] += p_col;
            }
        }
        buffer.sample_amount++;
        bytes.clear();
        for (size_t y = 0; y < image_height; y++) {
            for (size_t x = 0; x < image_width; x++) {
                auto color = buffer.get_pixel(y * image_width + x);
                color = glm::clamp(color, glm::vec3(0.0f), glm::vec3(1.0f));
                const auto [rbyte, gbyte, bbyte] =
                    color_to_bytes(buffer.get_pixel(y * image_width + x));
                bytes.push_back(rbyte);
                bytes.push_back(gbyte);
                bytes.push_back(bbyte);
            }
        }
    }

    void render_frame(const Hittable_list &world, Texture2D &texture) {
        calculate_pixels(buffer, world);
        UpdateTexture(texture, (void *)bytes.data());
    }

    void recalculate_camera() {
        projection =
            glm::perspectiveFov(glm::radians(vfov), (float)image_width,
                                (float)image_height, nearClip, farClip);
        inverseProjection = glm::inverse(projection);

        view =
            glm::lookAt(lookfrom, lookat + glm::vec3(0.0f, 0.0f, -1.0f), vup);
        inverseView = glm::inverse(view);
        rayDirections.resize(image_width * image_height);

        for (size_t y = 0; y < image_height; y++) {
            for (size_t x = 0; x < image_width; x++) {
                glm::vec2 coord = {(float)x / (float)image_width,
                                   (float)y / (float)image_height};
                coord = coord * 2.0f - 1.0f;

                glm::vec4 target =
                    inverseProjection * glm::vec4(coord.x, coord.y, 1, 1);
                glm::vec3 rayDirection = glm::vec3(
                    inverseView *
                    glm::vec4(glm::normalize(glm::vec3(target) / target.w), 0));
                rayDirections[x + y * image_width] = rayDirection;
            }
        }
    }

    void init() {
        image_height = (size_t)((fpoint)image_width / (fpoint)aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;
        buffer.init(image_width, image_height);
        bytes.reserve(buffer.pixels.capacity() * 3);

        recalculate_camera();
    }

   private:
    int image_height;
    fpoint vfov = 120;
    fpoint nearClip = 0.1f;
    fpoint farClip = 100.0f;
    glm::mat4 projection{1.0f};
    glm::mat4 view{1.0f};
    glm::mat4 inverseProjection{1.0f};
    glm::mat4 inverseView{1.0f};


    glm::vec3 random_in_unit_sphere() const {
        while (true) {
            glm::vec3 p;
            p.x = glm::linearRand(-1.0f, 1.0f);
            p.y = glm::linearRand(-1.0f, 1.0f);
            p.z = glm::linearRand(-1.0f, 1.0f);
            if (glm::dot(p, p) < 1) {
                return glm::normalize(p);
            }
        }
    }

    glm::vec3 random_in_hemisphere(const glm::vec3 &normal) const {
        glm::vec3 vec = random_in_unit_sphere();
        if (glm::dot(vec, normal) > 0.0) {
            return vec;
        } 
        return -vec;
    }

    [[nodiscard]]
    glm::vec3 ray_color(size_t x, size_t y, const Hittable_list &world) const {
        my_Ray ray;
        ray.orig = lookfrom;
        ray.dir = rayDirections[y * image_width + x];
        glm::vec3 color(0.0f);
        glm::vec3 contrib(1.0f);

        for (int i = 0; i < max_depth; i++) {
            Hit_record rec = world.hit(ray);
            if (rec.distance < 0.0f) {
                glm::vec3 skyColor = glm::vec3(0.5f, 0.7f, 0.9f);
                color += skyColor * contrib;
                break;
            }

            contrib *= world.objects[rec.index].color;

            ray.orig = rec.hitPoint + rec.normal * 0.0001f;
            ray.dir = glm::normalize(rec.normal + glm::sphericalRand(world.objects[rec.index].radius));
        }
        return color;
    }
};

#endif  // !CAMERA_H
