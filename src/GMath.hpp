#ifndef GMATH_H
#define GMATH_H

#include "header/debug.hpp"
#include "header/transform.hpp"

/**
 * Right-handed coordinate is default
 * Switch to Left-handed coordinate, open this macro
 */
// #define GM_USE_COORDINATE_LEFTHAND

namespace gm {

    typedef gm_vec3<int> ivec3;
    typedef gm_vec4<int> ivec4;

    typedef gm_vec3<float> vec3;
    typedef gm_vec4<float> vec4;
    typedef gm_quaternion<float> quaternion;

    typedef gm_mat3<float> mat3;
    typedef gm_mat4<float> mat4;

}

#endif // GMATH_H
