#include <climits>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include "camera.h"
#include "hittable_list.h"
#include "raylib.h"
#include "sphere.h"

int main() {
    constexpr size_t WIDTH = 1024;
    constexpr float ASPECT_RATIO = 16.0f / 9.0f;

    Hittable_list world;

    world.add(Sphere(glm::vec3(-1.f, +0.0f, -0.8f), +0.5f, {0.9f, +0.2f, +0.2f},
                     +0.4f));
    world.add(Sphere(glm::vec3(+0.0f, +0.0f, -0.8f), +0.5f,
                     {0.2f, +0.9f, +0.2f}, +0.4f));
    world.add(Sphere(glm::vec3(+1.0f, +0.0f, -0.8f), +0.5f,
                     {0.2f, +0.2f, +0.9f}, +0.4f));
    world.add(Sphere(glm::vec3(+1.f, +0.0f, +2.2f), +0.5f, {0.9f, +0.2f, +0.2f},
                     +0.4f));
    world.add(Sphere(glm::vec3(0.0f, +0.0f, +2.2f), +0.5f, {0.2f, +0.9f, +0.2f},
                     +0.4f));
    world.add(Sphere(glm::vec3(-1.0f, +0.0f, +2.2f), +0.5f,
                     {0.2f, +0.2f, +0.9f}, +0.4f));
    world.add(
        Sphere(glm::vec3(0, -1000.5f, -1), 1000, {0.3f, +0.3f, +0.6f}, +0.3f));

    TracingCamera cam;
    cam.max_depth = 5; 
    cam.aspect_ratio = ASPECT_RATIO;
    cam.image_width = WIDTH;
    cam.samples_per_pixel = 256;
    cam.lookfrom = glm::vec3(0, 0, 1);
    cam.lookat = glm::vec3(0.0f, 0.0f, -1.f);
    cam.init();

    InitWindow((int)cam.image_width, (int)cam.get_height(), "Rays");
    SetWindowMonitor(0);
    SetTargetFPS(60);
    Image image =
        GenImageColor((int)cam.image_width, (int)cam.get_height(), BLACK);
    ImageFormat(&image, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    Texture2D texture = LoadTextureFromImage(image);

    while (!WindowShouldClose()) {
        auto fps = GetFPS();
        glm::vec3 right_dir = glm::cross(cam.lookat, cam.vup);
        float cam_speed = 0.1f;
        if (IsKeyDown(KEY_LEFT_SHIFT)) {
            cam_speed = 300.0f;
        }
        if (IsKeyDown(KEY_W)) {
            cam.lookfrom += (cam.lookat * cam_speed);
            cam.recalculate_camera();
            cam.buffer.reset();
        }
        if (IsKeyDown(KEY_S)) {
            cam.lookfrom -= (cam.lookat * cam_speed);
            cam.recalculate_camera();
            cam.buffer.reset();
        }
        if (IsKeyDown(KEY_A)) {
            cam.lookfrom -= (right_dir * cam_speed);
            cam.recalculate_camera();
            cam.buffer.reset();
        }
        if (IsKeyDown(KEY_D)) {
            cam.lookfrom += (right_dir * cam_speed);
            cam.recalculate_camera();
            cam.buffer.reset();
        }
        if (IsKeyDown(KEY_Q)) {
            cam.lookfrom -= (cam.vup * cam_speed);
            cam.recalculate_camera();
            cam.buffer.reset();
        }
        if (IsKeyDown(KEY_E)) {
            cam.lookfrom += (cam.vup * cam_speed);
            cam.recalculate_camera();
            cam.buffer.reset();
        }
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            Vector2 mouseDelta = GetMouseDelta();
            if (mouseDelta.x != 0.0f || mouseDelta.y != 0.0f) {
                mouseDelta.x *= 0.03f;
                mouseDelta.y *= 0.03f;
                glm::quat q = glm::normalize(
                    glm::cross(glm::angleAxis(-mouseDelta.y, right_dir),
                               glm::angleAxis(-mouseDelta.x, cam.vup)));
                cam.lookat = glm::rotate(q, cam.lookat);
                cam.recalculate_camera();
                cam.buffer.reset();
            }
        }

        cam.render_frame(world, texture);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTextureRec(texture,
                       Rectangle{0, 0, static_cast<float>((int)cam.image_width),
                                 static_cast<float>(-(int)cam.get_height())},
                       Vector2{0, 0}, WHITE);
        DrawText(std::to_string(fps).c_str(), 10, 10, 24, DARKGRAY);
        DrawText(std::to_string(cam.buffer.sample_amount).c_str(), 10, 30, 24,
                 DARKGRAY);
        DrawText(std::to_string(cam.lookfrom.x).c_str(), 10, 50, 24, DARKGRAY);
        DrawText(std::to_string(cam.lookfrom.y).c_str(), 10, 70, 24, DARKGRAY);
        DrawText(std::to_string(cam.lookfrom.z).c_str(), 10, 90, 24, DARKGRAY);

        EndDrawing();
    }

    return 0;
}
