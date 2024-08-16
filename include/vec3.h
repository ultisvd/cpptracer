#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>
#include "declarations.h"

class vec3 {
   public:
    fpoint e[3];
    vec3() : e{0, 0, 0} {}
    vec3(fpoint e0, fpoint e1, fpoint e2) : e{e0, e1, e2} {}

    fpoint x() const;
    fpoint y() const;
    fpoint z() const;

    vec3 operator-() const;
    fpoint operator[](int i) const;
    fpoint &operator[](int i);

    vec3 &operator+=(const vec3 &v);
    vec3 &operator*=(fpoint t);
    vec3 &operator/=(fpoint t);

    fpoint length() const;

    fpoint length_squared() const;
};

using point3 = vec3;

inline std::ostream &operator<<(std::ostream &out, const vec3 &v);

vec3 operator+(const vec3 &u, const vec3 &v);

vec3 operator-(const vec3 &u, const vec3 &v);

vec3 operator*(const vec3 &u, const vec3 &v);

vec3 operator*(fpoint t, const vec3 &v);

vec3 operator*(const vec3 &v, fpoint t);

vec3 operator/(const vec3 &v, fpoint t);

fpoint dot(const vec3 &u, const vec3 &v);

vec3 cross(const vec3 &u, const vec3 &v);

vec3 normalize(const vec3 &v);

vec3 vec3_random();
vec3 vec3_random(fpoint min, fpoint max);
inline vec3 random_in_unit_sphere() {
    while (true) {
        auto p = vec3_random(-1, 1);
        if (p.length_squared() < 1)
            return p;
    }
}

inline vec3 random_unit_vector() {
    return normalize(random_in_unit_sphere());
}

inline vec3 random_on_hemisphere(const vec3 &normal) {
    vec3 on_unit_sphere = random_unit_vector();
    if (dot(on_unit_sphere, normal) > 0.0)
        return on_unit_sphere;
    else
        return -on_unit_sphere;
}
#endif  // !VEC3_H
