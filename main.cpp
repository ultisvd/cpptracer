#include "SDL2/SDL.h"
#include "camera.h"
#include "hittable_list.h"
#include "sphere.h"

// TODO: MOVE TO RAYLIB
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <climits>

int main() {
    Hittable_list world;

    world.add(Sphere(point3(0, 0, -1.3), 0.5));
    world.add(Sphere(point3(1, 0, -1.3), 0.5));
    world.add(Sphere(point3(-2, 0, -1.5), 0.5));
    world.add(Sphere(point3(2, 0, -1.5), 0.5));
    world.add(Sphere(point3(1.4, -0.4, -0.8), 0.1));
    world.add(Sphere(point3(-0.8, -0.4, -0.6), 0.1));
    world.add(Sphere(point3(0, -100.5, -1), 100));

    Camera cam;
    cam.max_depth = 256;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 1920;
    cam.samples_per_pixel = 1024;
    cam.lookfrom = point3(-0.4,0.3,0);
    cam.init();


    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        std::clog << "Epic SDL fail!" << '\n';
        return 1;
    }
    SDL_Window *window = SDL_CreateWindow(
        "Rays", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        (int)cam.image_width, (int)cam.get_height(), SDL_WINDOW_SHOWN);

    if (!window) {
        std::clog << "Couldn't create a window. \n";
        return 1;
    }

    SDL_Renderer *renderer =
        SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture *rayTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                                             SDL_TEXTUREACCESS_STREAMING,
                                             (int)cam.image_width, (int)cam.get_height());

    if (!renderer) {
        std::clog << "Couldn't create a renderer. \n";
        return 1;
    }

    SDL_Event event;
    SDL_PixelFormat *format = SDL_AllocFormat(SDL_PIXELFORMAT_ARGB8888);
    bool quit = false;
    // main game loop
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            }
        }
        cam.render_frame(world, rayTexture, format);

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, rayTexture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}
