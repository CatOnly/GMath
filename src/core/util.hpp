#ifndef GM_UTIL_H
#define GM_UTIL_H

#include <math.h>


// Frequent calls to assert are inefficient
#if GM_DEBUG == GM_DEBUG_ON
#   include <cassert>
#   define GM_ASSERT(val) assert(val)
#else
#   define GM_ASSERT(val)
#endif

#define GM_PI     3.14159265
// PI * 1/2
#define GM_PI_1_2 1.57079633
// PI * 3/2
#define GM_PI_3_2 4.71238898
// PI / 180.0
#define GM_ANGLE_TO_RADIAN 0.017453

namespace gm {

    template<typename T>
    T radians(const T angle){
        return angle * static_cast<T>(GM_ANGLE_TO_RADIAN);
    }

    template<typename T>
    T acosSafe(const T &angle){
        if (angle <= -1) {
            return static_cast<T>(GM_PI);
        } else if (angle >= 1) {
            return static_cast<T>(0);
        } else {
            return static_cast<T>(acos(angle));
        }
    }

    template<typename T>
    T asinSafe(const T &angle){
        if (angle <= -1) {
            return static_cast<T>(GM_PI_3_2);
        } else if (angle >= 1) {
            return static_cast<T>(GM_PI_1_2);
        } else {
            return static_cast<T>(asin(angle));
        }
    }
}

#endif // GM_UTIL_H
