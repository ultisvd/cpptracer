#include "SDL2/SDL.h"
#include "camera.h"
#include "hittable_list.h"
#include "sphere.h"
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
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
    cam.max_depth = 4;
    cam.aspect_ratio = 4.0 / 3.0;
    cam.image_width = 100;
    cam.samples_per_pixel = 32;
    cam.init();

    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        std::clog << "Epic SDL fail!" << '\n';
        return 1;
    }
    SDL_Window *window = SDL_CreateWindow(
        "Rays", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        cam.image_width, cam.get_height(), SDL_WINDOW_SHOWN);

    if (!window) {
        std::clog << "Couldn't create a window. \n";
        return 1;
    }

    SDL_Surface *screen = SDL_GetWindowSurface(window);
    SDL_Surface *back_buffer = SDL_CreateRGBSurfaceWithFormat(
        0, cam.image_width, cam.get_height(), 32, SDL_PIXELFORMAT_ARGB8888);
    // SDL_Renderer *renderer =
    //     SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // if (!renderer) {
    //     std::clog << "Couldn't create a renderer. \n";
    //     return 1;
    // }

    SDL_Event event;
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
        cam.render(world, back_buffer);

        SDL_BlitSurface(back_buffer, NULL, screen, NULL);
        SDL_UpdateWindowSurface(window);
        // SDL_RenderPresent(renderer);
    }

    // SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}
