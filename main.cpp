#include "hittable_list.h"
#include "sphere.h"
#include <climits>
#include "camera.h"


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
    cam.aspect_ratio = 16.0/9.0;
    cam.image_width = 1024;
    cam.samples_per_pixel = 32;

    cam.render(world);

    return 0;
}
