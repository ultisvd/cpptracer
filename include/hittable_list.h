#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <memory>
#include <vector>
#include "hittable.h"
#include "sphere.h"

using std::make_shared;
using std::shared_ptr;
using std::vector;

class Hittable_list {
   public:
    vector<Sphere> objects;

    Hittable_list() {}

    void clear() { objects.clear(); }

    void add(Sphere object) { objects.push_back(object); }

    bool hit(const my_Ray &ray, Interval ray_t, Hit_record &rec) const {
        auto closest_so_far = ray_t.max;
        bool hit_anything = false;
        Hit_record temp_rec;

        for (const auto &object : objects) {
            if (object.hit(ray, Interval(ray_t.min, closest_so_far),
                           temp_rec)) {
                rec = temp_rec;
                closest_so_far = rec.t;
                hit_anything = true;
            }
        }

        return hit_anything;
    };
};

#endif  // !HITTABLE_LIST_H
