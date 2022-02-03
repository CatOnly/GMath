#ifndef GM_COMMON_H
#define GM_COMMON_H

#include <iostream>
#include <iomanip>
#include <math.h>

#define GM_OUTPUT_WIDTH 0
#define GM_OUTPUT_PRECISION 2
#define GM_OUTPUT_FIXED

#define GM_RIGHT_HANDED 1
#define GM_LEFT_HANDED  0
#define GM_USE_COORDINATE GM_RIGHT_HANDED

#define GM_IS_Z_SCORPE_0_TO_1 1

#define GM_DEBUG_ON  1
#define GM_DEBUG_OFF 0
#define GM_DEBUG GM_DEBUG_OFF

// dependent define
#if GM_OUTPUT_PRECISION > 0
#define GM_OUTPUT_POINT_CMD showpoint
#else
#define GM_OUTPUT_POINT_CMD noshowpoint
#endif

#ifdef GM_OUTPUT_FIXED
#define GM_OUTPUT_FIXED_CMD fixed
#else
#define GM_OUTPUT_FIXED_CMD ""
#endif

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

	const static float EPS    = 1e-4;              // EPSILON
	const static float PI     = 3.1415926535897932f;
	const static float PI_2   = 6.2831853071795864f;
	const static float PI_1_2 = 1.57079632679f;    // PI * 1/2
	const static float PI_3_2 = 4.71238898038f;    // PI * 3/2
	const static float ANGLE_TO_RADIAN = 0.01745329251994f;  // PI / 180.0
	const static float RADIAN_TO_ANGLE = 57.2957795130823f;  // 180.0 / PI

    inline static float sqrt(const float v) {
        return sqrtf(v);
    }

    inline static float acos(const float angle) {
        if (angle <= -1) {
            return PI;
        } else if (angle >= 1) {
            return 0;
        } else {
            return acosf(angle);
        }
    }

    inline static float asin(const float angle){
        if (angle <= -1) {
            return PI_3_2;
        } else if (angle >= 1) {
            return PI_1_2;
        } else {
            return asinf(angle);
        }
    }

    inline static float sin(const float v)
    {
        return sinf(v);
    }

    inline static float cos(const float v)
    {
        return cosf(v);
    }

    inline static float tan(const float v)
    {
        return tanf(v);
    }

    inline static float atan(const float v)
    {
        return atanf(v);
    }

    inline static float atan2(const float Y, const float X)
    {
        //return atan2f(Y,X);
        // atan2f occasionally returns NaN with perfectly valid input (possibly due to a compiler or library bug).
        // We are replacing it with a minimax approximation with a max relative error of 7.15255737e-007 compared to the C library function.
        // On PC this has been measured to be 2x faster than the std C version.

        const float absX = GM_ABS(X);
        const float absY = GM_ABS(Y);
        const bool yAbsBigger = (absY > absX);
        float t0 = yAbsBigger ? absY : absX; // Max(absY, absX)
        float t1 = yAbsBigger ? absX : absY; // Min(absX, absY)
        
        if (t0 == 0.f)
            return 0.f;

        float t3 = t1 / t0;
        float t4 = t3 * t3;

        static const float c[7] = {
            +7.2128853633444123e-03f,
            -3.5059680836411644e-02f,
            +8.1675882859940430e-02f,
            -1.3374657325451267e-01f,
            +1.9856563505717162e-01f,
            -3.3324998579202170e-01f,
            +1.0f
        };

        t0 = c[0];
        t0 = t0 * t4 + c[1];
        t0 = t0 * t4 + c[2];
        t0 = t0 * t4 + c[3];
        t0 = t0 * t4 + c[4];
        t0 = t0 * t4 + c[5];
        t0 = t0 * t4 + c[6];
        t3 = t0 * t3;

        t3 = yAbsBigger ? (0.5f * PI) - t3 : t3;
        t3 = (X < 0.0f) ? PI - t3 : t3;
        t3 = (Y < 0.0f) ? -t3 : t3;

        return t3;
    }

} // namespace gm

#endif // GM_COMMON_H
