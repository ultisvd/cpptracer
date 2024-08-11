#include "vec3.h"

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

std::ostream &operator<<(std::ostream &out, const vec3 &v) {
    return out << v.x() << ' ' << v.y() << ' ' << v.z();
}

vec3 operator+(const vec3 &u, const vec3 &v) {
    return vec3(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
}

vec3 operator-(const vec3 &u, const vec3 &v) {
    return vec3(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
}

vec3 operator*(const vec3 &u, const vec3 &v) {
    return vec3(u.x() * v.x(), u.y() * v.y(), u.z() * v.z());
}

vec3 operator*(fpoint t, const vec3 &v) {
    return vec3(v.x() * t, v.y() * t, v.z() * t);
}

vec3 operator*(const vec3 &v, fpoint t) { return t * v; }

vec3 operator/(const vec3 &v, fpoint t) { return v * (1 / t); }

fpoint dot(const vec3 &u, const vec3 &v) {
    return u.x() * v.x() + u.y() * v.y() + u.z() * v.z();
}

vec3 cross(const vec3 &u, const vec3 &v) {
    const auto x = u.y() * v.z() - u.z() * v.y(); // x = AyBz - AzBy
    const auto y = u.z() * v.x() - u.x() * v.z(); // y = AzBx - AxBz
    const auto z = u.x() * v.y() - u.y() * v.x(); // z = AxBy - AyBx
    return vec3(x, y, z);
}

vec3 normalize(const vec3 &v) { return v / v.length(); }
