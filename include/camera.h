#ifndef CAMERA_H
#define CAMERA_H



#include "declarations.h"
#include <sys/types.h>
#include <algorithm>
#include <execution>
#include "hittable_list.h"
#include "ray.h"
#include "rtweekend.h"

struct pixel_buffer {
    vector<glm::vec3> pixels;
    int sample_amount = 0;
    size_t width, height;
    void init(size_t width, size_t height) {
        pixels.reserve(width * height);
        for (size_t i = 0; i < pixels.capacity(); i++) {
            pixels.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
        }
    }
    glm::vec3 get_pixel(size_t index) {
        return pixels[index] / (float)sample_amount;
    }
    void reset() {
        pixels.clear();
        sample_amount = 0;
        for (size_t i = 0; i < pixels.capacity(); i++) {
            pixels.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
        }
    }
};

class TracingCamera {
   public:
    size_t image_width;
    float aspect_ratio;
    int samples_per_pixel;
    int max_depth;
    pixel_buffer buffer;
    glm::vec3 lookfrom = glm::vec3(0, 0, 0);
    glm::vec3 lookat = glm::vec3(0, 0, -1);
    glm::vec3 vup = glm::vec3(0, 1, 0);
    std::vector<glm::vec3> rayDirections;
    std::vector<size_t> horiIter;
    std::vector<size_t> vertIter;

    vector<Color> bytes;

    [[nodiscard]]
    size_t get_height() const;

    void calculate_pixels(pixel_buffer &buffer, const Hittable_list &world);


    void recalculate_camera();

    void init();

   private:
    size_t image_height;
    float vfov = 45;
    float nearClip = 0.1f;
    float farClip = 100.0f;
    glm::mat4 projection{1.0f};
    glm::mat4 view{1.0f};
    glm::mat4 inverseProjection{1.0f};
    glm::mat4 inverseView{1.0f};

    [[nodiscard]]
    glm::vec3 ray_color(size_t x, size_t y, const Hittable_list &world) const;
};

#endif  // !CAMERA_H
