#include <climits>
#include "camera.h"
#include "hittable_list.h"
#include "raylib.h"
#include "sphere.h"


int main() {
    Hittable_list world;

    world.add(Sphere(point3(0, 0, -1.3), 0.51));
    world.add(Sphere(point3(1, 0, -1.3), 0.51));
    world.add(Sphere(point3(-2, 0, -1.5), 0.51));
    world.add(Sphere(point3(2, 0, -1.5), 0.51));
    world.add(Sphere(point3(1.4, -0.4, -0.8), 0.11));
    world.add(Sphere(point3(-0.8, -0.4, -0.6), 0.11));
    world.add(Sphere(point3(0, -100.5, -1), 100));

    TracingCamera cam;
    cam.max_depth = 8;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 1600;
    cam.samples_per_pixel = 256;
    cam.lookfrom = point3(-0.4, -0.35, 0);
    cam.lookat = point3(0, 0, -0.9);
    cam.init();

    InitWindow(cam.image_width, cam.get_height(), "Rays");
    SetWindowMonitor(0);
    SetTargetFPS(60);
    RenderTexture2D target =
        LoadRenderTexture(cam.image_width, cam.get_height());

    while (!WindowShouldClose()) {
        auto fps = GetFPS();
        cam.render_frame(world, target);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTextureRec(target.texture, Rectangle{0, 0,
                       float(target.texture.width),
                       float(-target.texture.height)}, Vector2{0, 0}, WHITE);
        DrawText(std::to_string(fps).c_str(), 100, 100, 24, RED);

        EndDrawing();
    }
    // if (SDL_Init(SDL_INIT_EVERYTHING)) {
    //     std::clog << "Epic SDL fail!" << '\n';
    //     return 1;
    // }
    // SDL_Window *window = SDL_CreateWindow(
    //     "Rays", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    //     (int)cam.image_width, (int)cam.get_height(), SDL_WINDOW_SHOWN);
    //
    // if (!window) {
    //     std::clog << "Couldn't create a window. \n";
    //     return 1;
    // }
    //
    // SDL_Renderer *renderer =
    //     SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // SDL_Texture *rayTexture = SDL_CreateTexture(
    //     renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
    //     (int)cam.image_width, (int)cam.get_height());
    //
    // if (!renderer) {
    //     std::clog << "Couldn't create a renderer. \n";
    //     return 1;
    // }
    //
    // SDL_Event event;
    // SDL_PixelFormat *format = SDL_AllocFormat(SDL_PIXELFORMAT_ARGB8888);
    // bool quit = false;
    // // main game loop
    // while (!quit) {
    //     while (SDL_PollEvent(&event)) {
    //         switch (event.type) {
    //             case SDL_QUIT:
    //                 quit = true;
    //                 break;
    //         }
    //     }
    //     cam.render_frame(world, rayTexture, format);
    //
    //     SDL_RenderClear(renderer);
    //     SDL_RenderCopy(renderer, rayTexture, NULL, NULL);
    //     SDL_RenderPresent(renderer);
    // }
    //
    // SDL_DestroyRenderer(renderer);
    // SDL_Quit();

    return 0;
}
