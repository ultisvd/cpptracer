#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h" 
#include <memory>
#include <vector>

using std::make_shared;
using std::shared_ptr;
using std::vector;

class Hittable_list : public Hittable {
public:
    vector<shared_ptr<Hittable>> objects;

    Hittable_list() {}
    Hittable_list(shared_ptr<Hittable> object) {add(object);}

    void clear() {objects.clear();}

    void add(shared_ptr<Hittable> object) {
        objects.push_back(object);
    }

    std::optional<Hit_record> hit(const Ray& ray, fpoint ray_tmin, fpoint ray_tmax) const override {
        auto closest_so_far = ray_tmax;

        for (const auto object : objects) {
            auto ray_hit = hit(ray, ray_tmin, ray_tmax);
            if (ray_hit){
                auto rec = ray_hit.value();
                closest_so_far = rec.t;
                return rec;
            }
        }
        
        return std::nullopt;
    };
};


#endif // !HITTABLE_LIST_H

