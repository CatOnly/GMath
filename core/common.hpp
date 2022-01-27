#ifndef GM_COMMON_H
#define GM_COMMON_H

#include <iostream>
#include <iomanip>
#include <math.h>

// Frequent calls to assert are inefficient
#if GM_DEBUG == GM_DEBUG_ON
#   include <cassert>
#   define GM_ASSERT(val) assert(val)
#else
#   define GM_ASSERT(val)
#endif

#ifndef GM_MAX
#define GM_MAX(a,b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef GM_MIN
#define GM_MIN(a,b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef GM_CLAMP
#define GM_CLAMP(min, max, val) ( ((val) < (min)) ? (min) : ( ((val) > (min)) ? (max) : (val) ) )
#endif

#ifndef GM_ABS
#define GM_ABS(x) ((x) < 0 ? (-(x)) : (x))
#endif

#ifndef GM_FRACT
#define GM_FRACT(x) ((x) - int(x))
#endif

#ifndef GM_REPEAT
#define GM_REPEAT(x) ((x) > 0 ? GM_FRACT(x) : 1.0 - (int(x) - (x)))
#endif

#ifndef GM_REPEAT_MIRROR
#define GM_REPEAT_MIRROR(x) ((x) > 0 ? 1.0 - ((x) - int(x)) : int(x) - (x))
#endif

#ifndef GM_RADIANS
#define GM_RADIANS(x) ((x) * gm::ANGLE_TO_RADIAN)
#endif

#ifndef GM_ANGLES
#define GM_ANGLES(x) ((x) * gm::RADIAN_TO_ANGLE)
#endif

#ifndef GM_LERP
#define GM_LERP(a,b,w) ((a) + (w) * ((b) - (a)))
#endif

#ifndef GM_LERP3
#define GM_LERP3(a,b,c,d,w1,w2) GM_LERP(GM_LERP(a,b,w1), GM_LERP(c,d,w1), w2)
#endif

namespace gm {

	const static double EPS    = 1e-5;              // EPSILON
	const static double PI     = 3.141592653589793;
	const static double PI_2   = 6.283185307179586;
	const static double PI_1_2 = 1.570796326794897; // PI * 1/2
	const static double PI_3_2 = 4.71238898038469;  // PI * 3/2
	const static double ANGLE_TO_RADIAN = 0.01745329251994;  // PI / 180.0
	const static double RADIAN_TO_ANGLE = 57.2957795130823;  // 180.0 / PI 

    template<typename T>  class gm_vec3;
    template<typename T>  class gm_vec4;
    template<typename T>  class gm_quaternion;

    template<typename T>
    T acos(const T &angle){
        if (angle <= -1) {
            return static_cast<T>(PI);
        } else if (angle >= 1) {
            return static_cast<T>(0);
        } else {
            return static_cast<T>(std::acos(angle));
        }
    }

    template<typename T>
    T asin(const T &angle){
        if (angle <= -1) {
            return static_cast<T>(PI_3_2);
        } else if (angle >= 1) {
            return static_cast<T>(PI_1_2);
        } else {
            return static_cast<T>(std::asin(angle));
        }
    }

    template<typename T>
    T sin(const T v)
    {
        return std::sin(v);
    }

    template<typename T>
    T cos(const T v)
    {
        return std::cos(v);
    }

    template<typename T>
    gm_vec3<T> sin(const gm_vec3<T> &v);

    template<typename T>
    gm_vec3<T> cos(const gm_vec3<T> &v);

    template<typename T>
    gm_quaternion<T> pow(const gm_quaternion<T> &q, float exponent);

    template<typename T>
    gm_quaternion<T> lerp(const gm_quaternion<T> &q0, const gm_quaternion<T> &q1, float t);

    template<typename T>
    gm_quaternion<T> nlerp(const gm_quaternion<T> &q0, const gm_quaternion<T> &q1, float t);

    template<typename T>
    gm_quaternion<T> slerp(const gm_quaternion<T> &q0, const gm_quaternion<T> &q1, float t);
}

//#include "common.inl"

#endif // GM_COMMON_H
