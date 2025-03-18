#include <climits>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_pixels.h"
#include "SDL3/SDL_surface.h"
#include "SDL3/SDL_video.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <glm/gtx/quaternion.hpp>
#include "camera.h"
#include "hittable_list.h"
#include "sphere.h"

using vec3 = glm::vec3;

int main() {
    constexpr size_t WIDTH = 1024;
    constexpr float ASPECT_RATIO = 16.0f / 9.0f;

    Hittable_list world;

    world.add(Sphere(vec3(-60.f, +80.0f, -80.f), {0.9f, +0.2f, +0.2f},
                     vec3(1.f, 1.f, 1.f), 5.f, +40.0f));
    world.add(Sphere(vec3(-1.f, +0.0f, -0.8f), vec3(0.9f, +0.2f, +0.2f),
                     vec3(0.f, 0.f, 0.f), 0.f, +0.5f));
    world.add(Sphere(vec3(+0.0f, +0.0f, -0.8f), vec3(0.2f, +0.9f, +0.2f),
                     vec3(0.f, 0.f, 0.f), 0.f, +0.5f));
    world.add(Sphere(vec3(+1.0f, +0.0f, -0.8f), vec3(0.2f, +0.2f, +0.9f),
                     vec3(0.f, 0.f, 0.f), 0.f, +0.5f));
    world.add(Sphere(vec3(+1.f, +0.0f, +2.2f), vec3(0.9f, +0.2f, +0.2f),
                     vec3(0.f, 0.f, 0.f), 0.f, +0.5f));
    world.add(Sphere(vec3(0.0f, +0.0f, +2.2f), vec3(0.2f, +0.9f, +0.2f),
                     vec3(0.f, 0.f, 0.f), 0.f, +0.5f));
    world.add(Sphere(vec3(-1.0f, +0.0f, +2.2f), vec3(0.2f, +0.2f, +0.9f),
                     vec3(0.f, 0.f, 0.f), 0.f, +0.5f));
    world.add(Sphere(vec3(0, -1000.5f, -1), vec3(0.3f, +0.3f, +0.6f),
                     vec3(0.f, 0.f, 0.f), 0.f, 1000));

    TracingCamera cam;
    cam.max_depth = 5;
    cam.aspect_ratio = ASPECT_RATIO;
    cam.image_width = WIDTH;
    cam.samples_per_pixel = 256;
    cam.lookfrom = vec3(0, 0, 1);
    cam.lookat = vec3(0.0f, 0.0f, -1.f);
    cam.init();
    bool success_sdl;
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("frick my stupid baka life\n");
        success_sdl = false;
    }
    SDL_Window *window =
        SDL_CreateWindow("Rays", WIDTH, (int)(WIDTH / ASPECT_RATIO), 0);
    SDL_Surface *screen_surface = SDL_GetWindowSurface(window);
    SDL_Surface *render_surface = SDL_CreateSurface(
        WIDTH, (int)(WIDTH / ASPECT_RATIO), SDL_PIXELFORMAT_RGB24);
    bool is_running = true;
    SDL_SetWindowRelativeMouseMode(window, true);

    // InitWindow((int)cam.image_width, (int)cam.get_height(), "Rays");
    // SetWindowMonitor(0);
    // SetTargetFPS(60);
    // Image image =
    //     GenImageColor((int)cam.image_width, (int)cam.get_height(), BLACK);
    // ImageFormat(&image, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    // Texture2D texture = LoadTextureFromImage(image);

    while (is_running) {
        vec3 right_dir = glm::cross(cam.lookat, cam.vup);
        float cam_speed = 0.1f;
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                is_running = false;
            } else if (event.type == SDL_EVENT_KEY_DOWN) {
                switch (event.key.key) {
                    case SDLK_W:
                        cam.lookfrom += (cam.lookat * cam_speed);
                        cam.recalculate_camera();
                        cam.buffer.reset();
                        break;
                    case SDLK_S:
                        cam.lookfrom -= (cam.lookat * cam_speed);
                        cam.recalculate_camera();
                        cam.buffer.reset();
                        break;
                    case SDLK_A:
                        cam.lookfrom -= (right_dir * cam_speed);
                        cam.recalculate_camera();
                        cam.buffer.reset();
                        break;
                    case SDLK_D:
                        cam.lookfrom += (right_dir * cam_speed);
                        cam.recalculate_camera();
                        cam.buffer.reset();
                        break;
                    case SDLK_Q:
                        cam.lookfrom -= (cam.vup * cam_speed);
                        cam.recalculate_camera();
                        cam.buffer.reset();
                        break;
                    case SDLK_E:
                        cam.lookfrom += (cam.vup * cam_speed);
                        cam.recalculate_camera();
                        cam.buffer.reset();
                        break;
                    case SDLK_LSHIFT:
                        cam_speed = 100.0f;
                        break;
                    case SDLK_ESCAPE:
                        is_running = false;
                        break;
                }
            } else if (event.type == SDL_EVENT_MOUSE_MOTION) {
                float xrel = event.motion.xrel * 0.03f;
                float yrel = event.motion.yrel * 0.03f;
                glm::quat q =
                    glm::normalize(glm::cross(glm::angleAxis(-yrel, right_dir),
                                              glm::angleAxis(-xrel, cam.vup)));
                cam.lookat = glm::rotate(q, cam.lookat);
                cam.recalculate_camera();
                cam.buffer.reset();
            }
            // if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            //     Vector2 mouseDelta = GetMouseDelta();
            //     if (mouseDelta.x != 0.0f || mouseDelta.y != 0.0f) {
            //         mouseDelta.x *= 0.03f;
            //         mouseDelta.y *= 0.03f;
            //         glm::quat q = glm::normalize(
            //             glm::cross(glm::angleAxis(-mouseDelta.y, right_dir),
            //                        glm::angleAxis(-mouseDelta.x, cam.vup)));
            //         cam.lookat = glm::rotate(q, cam.lookat);
            //         cam.recalculate_camera();
            //         cam.buffer.reset();
            //     }
        }

        cam.calculate_pixels(cam.buffer, world);
        render_surface->pixels = (void *)cam.bytes.data();
        SDL_FlipSurface(render_surface, SDL_FLIP_VERTICAL);
        SDL_BlitSurface(render_surface, NULL, screen_surface, NULL);
        SDL_UpdateWindowSurface(window);
        // BeginDrawing();
        // ClearBackground(RAYWHITE);
        // DrawTextureRec(texture,
        //                Rectangle{0, 0, (float)((int)cam.image_width),
        //                          (float)(-(int)cam.get_height())},
        //                Vector2{0, 0}, WHITE);
        // DrawText(std::to_string(fps).c_str(), 10, 10, 24, DARKGRAY);
        // DrawText(std::to_string(cam.buffer.sample_amount).c_str(), 10, 30,
        // 24,
        //          DARKGRAY);
        // DrawText(std::to_string(cam.lookfrom.x).c_str(), 10, 50, 24,
        // DARKGRAY); DrawText(std::to_string(cam.lookfrom.y).c_str(), 10, 70,
        // 24, DARKGRAY); DrawText(std::to_string(cam.lookfrom.z).c_str(), 10,
        // 90, 24, DARKGRAY);
        //
        // EndDrawing();
    }

    return 0;
}
