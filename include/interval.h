#ifndef INTERVAL_H
#define INTERVAL_H

#include "declarations.h"

class Interval {
   public:
    fpoint min, max;
    Interval() : min(+infinity), max(-infinity) {}

    Interval(fpoint min, fpoint max) : min(min), max(max) {}

    fpoint size() const { return max - min; }

    bool contains(fpoint x) const { return min <= x && x <= max; }

    bool surrounds(fpoint x) const { return min < x && x < max; }

    fpoint clamp(fpoint x) const {
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
