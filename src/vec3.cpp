#include "vec3.h"
#include "rtweekend.h"

fpoint vec3::x() const { return e[0]; }
fpoint vec3::y() const { return e[1]; }
fpoint vec3::z() const { return e[2]; }

vec3 vec3::operator-() const { return vec3(-e[0], -e[1], -e[2]); }
fpoint vec3::operator[](int i) const { return e[i]; }
fpoint &vec3::operator[](int i) { return e[i]; }

vec3 &vec3::operator+=(const vec3 &v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
}

vec3 &vec3::operator*=(fpoint t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

vec3 &vec3::operator/=(fpoint t) { return *this *= 1 / t; }

fpoint vec3::length() const { return std::sqrt(length_squared()); }

fpoint vec3::length_squared() const {
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
}

vec3 vec3_random() {
    return vec3(random_fpoint(), random_fpoint(), random_fpoint());
}

vec3 vec3_random(fpoint min, fpoint max) {
    return vec3(random_fpoint(min, max), random_fpoint(min, max),
                random_fpoint(min, max));
}

std::ostream &operator<<(std::ostream &out, const vec3 &v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

vec3 operator+(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

vec3 operator-(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

vec3 operator*(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

vec3 operator*(fpoint t, const vec3 &v) {
    return vec3(v.e[0] * t, v.e[1] * t, v.e[2] * t);
}

vec3 operator*(const vec3 &v, fpoint t) { return t * v; }

vec3 operator/(const vec3 &v, fpoint t) { return v * (1 / t); }

fpoint dot(const vec3 &u, const vec3 &v) {
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

vec3 cross(const vec3 &u, const vec3 &v) {
    const auto x = u.e[1] * v.e[2] - u.e[2] * v.e[1]; // x = AyBz - AzBy
    const auto y = u.e[2] * v.e[0] - u.e[0] * v.e[2]; // y = AzBx - AxBz
    const auto z = u.e[0] * v.e[1] - u.e[1] * v.e[0]; // z = AxBy - AyBx
    return vec3(x, y, z);
}

vec3 normalize(const vec3 &v) { return v / v.length(); }
