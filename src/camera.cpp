#include "camera.h"

[[nodiscard]]
size_t TracingCamera::get_height() const {
    return image_height;
}

void TracingCamera::calculate_pixels(pixel_buffer &buffer, const Hittable_list &world) {
#define MT 1
#if MT
    buffer.sample_amount++;
    std::for_each(
        std::execution::par, vertIter.begin(), vertIter.end(), [&](size_t y) {
            std::for_each(std::execution::par, horiIter.begin(), horiIter.end(),
                          [&](size_t x) {
                              glm::vec3 color = ray_color(x, y, world);
                              buffer.pixels[x + y * image_width] += color;
                              auto accumColor =
                                  buffer.get_pixel(x + y * image_width);
                              accumColor = glm::clamp(
                                  accumColor, glm::vec3(0.0f), glm::vec3(1.0f));
                              const auto [rbyte, gbyte, bbyte] =
                                  color_to_bytes(accumColor);
                              Color byte_color;
                              byte_color.r = rbyte;
                              byte_color.g = gbyte;
                              byte_color.b = bbyte;
                              byte_color.a = 255;
                              bytes[x + y * image_width] = byte_color;
                          });
        });

#else
    buffer.sample_amount++;
    for (size_t y = 0; y < image_height; y++) {
        for (size_t x = 0; x < image_width; x++) {
            glm::vec3 color = ray_color(x, y, world);
            buffer.pixels[x + y * image_width] += color;
            auto accumColor = buffer.pixels[x + y * image_width] /
                              (float)buffer.sample_amount;
            accumColor =
                glm::clamp(accumColor, glm::vec3(0.0f), glm::vec3(1.0f));
            const auto [rbyte, gbyte, bbyte] = color_to_bytes(accumColor);
            Color byte_color;
            byte_color.r = rbyte;
            byte_color.g = gbyte;
            byte_color.b = bbyte;
            byte_color.a = 255;
            bytes[x + y * image_width] = byte_color;
        }
    }
#endif
}

void TracingCamera::render_frame(const Hittable_list &world, Texture2D &texture) {
    calculate_pixels(buffer, world);
    UpdateTexture(texture, (void *)bytes.data());
}

void TracingCamera::recalculate_camera() {
    projection = glm::perspectiveFov(glm::radians(vfov), (float)image_width,
                                     (float)image_height, nearClip, farClip);
    inverseProjection = glm::inverse(projection);

    view = glm::lookAt(lookfrom, lookfrom + lookat, vup);
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

void TracingCamera::init() {
    image_height = (size_t)((float)image_width / (float)aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;
    buffer.init(image_width, image_height);
    bytes.reserve(image_width * image_height);
    for (size_t i = 0; i < image_height; i++) {
        vertIter.push_back(i);
    }
    for (size_t i = 0; i < image_width; i++) {
        horiIter.push_back(i);
    }
    for (size_t j = 0; j < image_height; j++) {
        for (size_t i = 0; i < image_width; i++) {
            Color newColor{.r = 255, .g = 255, .b = 255, .a = 255};
            bytes.push_back(newColor);
        }
    }

    recalculate_camera();
}
    [[nodiscard]]
    glm::vec3 TracingCamera::ray_color(size_t x, size_t y, const Hittable_list &world) const {
        my_Ray ray;
        ray.orig = lookfrom;
        ray.dir = rayDirections[y * image_width + x];
        glm::vec3 color(0.0f);
        glm::vec3 contrib(1.0f);

        for (int i = 0; i < max_depth; i++) {
            Hit_record rec = world.hit(ray);
            if (rec.distance < 0.0f) {
                glm::vec3 skyColor = glm::vec3(0.7f, 0.7f, 0.9f);
                color += skyColor * contrib;
                break;
            }

            const Sphere &sphere = world.objects[rec.index];
            contrib *= sphere.color;

            ray.orig = rec.hitPoint + rec.normal * 0.0001f;
            glm::vec3 rand;
            rand.x = random_float(-0.5f, 0.5f);
            rand.y = random_float(-0.5f, 0.5f);
            rand.z = random_float(-0.5f, 0.5f);
            ray.dir = glm::reflect(
                ray.dir, rec.normal + sphere.roughness *
                                          rand);
        }
        return color;
    }
