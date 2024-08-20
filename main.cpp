#include <climits>
#include "camera.h"
#include "hittable_list.h"
#include "raylib.h"
#include "sphere.h"

int main() {
    constexpr size_t WIDTH = 800;
    constexpr fpoint ASPECT_RATIO = 16.0f / 9.0f;

    Hittable_list world;

    world.add(Sphere(glm::vec3(0.0f, 0.0f, -1.3f), 2.0f, {0.95f, 0.0f, 0.95f}));
    world.add(Sphere(glm::vec3(-4.f, 0.0f, -1.5f), 2.0f, {0.9f, 0.9f, 0.0f}));
    // world.add(Sphere(glm::vec3(0.0f, 0.0f, -2.1f), 0.51f, {0.8f, 0.1f, 0.1f}));
    world.add(Sphere(glm::vec3(0, -102, -1), 100, {0.0f, 0.6f, 0.8f}));

    TracingCamera cam;
    cam.max_depth = 5;
    cam.aspect_ratio = ASPECT_RATIO;
    cam.image_width = WIDTH;
    cam.samples_per_pixel = 256;
    cam.lookfrom = glm::vec3(0, 0, 0);
    cam.lookat = glm::vec3(0.0f, 0.0f, -1.f);
    cam.init();

    InitWindow(cam.image_width, cam.get_height(), "Rays");
    SetWindowMonitor(0);
    SetTargetFPS(60);
    Image image = GenImageColor(cam.image_width, cam.get_height(), BLACK);
    ImageFormat(&image, PIXELFORMAT_UNCOMPRESSED_R8G8B8);
    Texture2D texture = LoadTextureFromImage(image);

    while (!WindowShouldClose()) {
        auto fps = GetFPS();
        if (IsKeyDown(KEY_W)) {
            cam.lookfrom.z -= 0.05f;
            cam.recalculate_camera();
            cam.buffer.reset();
        }
        if (IsKeyDown(KEY_A)) {
            cam.lookfrom.x -= 0.05f;
            cam.recalculate_camera();
            cam.buffer.reset();
        }
        if (IsKeyDown(KEY_S)) {
            cam.lookfrom.z += 0.05f;
            cam.recalculate_camera();
            cam.buffer.reset();
        }
        if (IsKeyDown(KEY_D)) {
            cam.lookfrom.x += 0.05f;
            cam.recalculate_camera();
            cam.buffer.reset();
        }
        if (IsKeyDown(KEY_Y)) {
            cam.lookfrom.y += 0.05f;
            cam.recalculate_camera();
            cam.buffer.reset();
        }
        if (IsKeyDown(KEY_H)) {
            cam.lookfrom.y -= 0.05f;
            cam.recalculate_camera();
            cam.buffer.reset();
        }

        cam.render_frame(world, texture);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTextureRec(texture,
                       Rectangle{0, 0, static_cast<float>(cam.image_width),
                                 static_cast<float>(-cam.get_height())},
                       Vector2{0, 0}, WHITE);
        DrawText(std::to_string(fps).c_str(), 10, 10, 24, DARKGRAY);
        DrawText(std::to_string(cam.buffer.sample_amount).c_str(), 10, 30, 24,
                 DARKGRAY);

        EndDrawing();
    }

    return 0;
}
