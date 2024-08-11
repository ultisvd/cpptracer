#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

using fpoint = float;

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

using point = vec3;

inline std::ostream &operator<<(std::ostream &out, const vec3 &v);

vec3 operator+(const vec3 &u, const vec3 &v);

vec3 operator-(const vec3 &u, const vec3 &v);

vec3 operator*(const vec3 &u, const vec3 &v);

vec3 operator*(fpoint t, const vec3 &v);

vec3 operator*(const vec3 &v, fpoint t);

vec3 operator/(const vec3 &v, fpoint t);

fpoint dot(const vec3 &u, const vec3 &v);

vec3 cross(const vec3 &u, const vec3 &v);

vec3 normalize(const vec3& v);

#endif // !VEC3_H
