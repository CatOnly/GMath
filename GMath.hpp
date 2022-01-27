#ifndef GMATH_H
#define GMATH_H

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

#include "core/color.hpp"
#include "core/graphics.hpp"
#include "core/geometric.hpp"
#include "core/transform2D.hpp"
#include "core/transform3D.hpp"

namespace gm {

    typedef gm_vec2<int> Size;
    typedef gm_vec3<int> Face;
    typedef gm_vec4<int> Viewport;

    typedef gm_vec2<float> Vec2;
    typedef gm_vec3<float> Vec3;
    typedef gm_vec4<float> Vec4;

    typedef gm_mat2<float> Mat2;
    typedef gm_mat3<float> Mat3;
    typedef gm_mat4<float> Mat4;

    typedef gm_quaternion<float> Quat;

    typedef gm_transform2D<float> Transform2D;
    typedef gm_transform3D<float> Transform;

}

#endif // GMATH_H
