#ifndef GMATH_H
#define GMATH_H

#include "core/color.hpp"
#include "core/graphics.hpp"
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
