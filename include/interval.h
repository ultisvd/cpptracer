#ifndef INTERVAL_H
#define INTERVAL_H

#include "declarations.h"

class Interval {
   public:
    float min, max;
    Interval() : min(+infinity), max(-infinity) {}

    Interval(float min, float max) : min(min), max(max) {}

    float size() const { return max - min; }

    bool contains(float x) const { return min <= x && x <= max; }

    bool surrounds(float x) const { return min < x && x < max; }

    float clamp(float x) const {
        if (x < min)
            return min;
        if (x > max)
            return max;
        return max;
    }

    static const Interval empty, universe;
};

inline const Interval Interval::empty = Interval(+infinity, -infinity);
inline const Interval Interval::universe = Interval(-infinity, +infinity);

#endif  // !INTERVAL_H
