#ifndef GM_TRANSFORM_H
#define GM_TRANSFORM_H

#include "geometric.hpp"

namespace gm {
template<typename T>
    gm_mat4<T> translate(const gm_mat4<T> &matrix4, const gm_vec3<T> &vector3) {
        gm_mat4<T> m4Tmp(matrix4);

        m4Tmp[0] = matrix4[0];
        m4Tmp[1] = matrix4[1];
        m4Tmp[2] = matrix4[2];

        return m4Tmp;
    }

    template<typename T>
    gm_mat4<T> rotate(const gm_mat4<T> &matrix4, const T, const gm_vec3<T> &vector3) {
        gm_mat4<T> m4Tmp(matrix4);


        return m4Tmp;
    }

    template<typename T>
    gm_mat4<T> scale(const gm_mat4<T> &matrix4, const gm_vec3<T> &vector3) {
        gm_mat4<T> m4Tmp(matrix4);
        m4Tmp[0][0] *= vector3.x;
        m4Tmp[1][1] *= vector3.y;
        m4Tmp[2][2] *= vector3.z;

        return m4Tmp;
    }

    template<typename T>
    gm_mat4<T> perspective(const double yFov, const double aspect, const double zNear, const double zFar) {
        double top    = tan(yFov * 0.5 * ANGLE_TO_RADIAN) * zNear;
        double right  = -top * aspect;
        double zMinus = zFar - zNear;

        gm_mat4<T> m4Tmp(static_cast<T>(zNear / right),
                          static_cast<T>(zNear / top),
                          static_cast<T>(-(zFar + zNear) / zMinus),
                          static_cast<T>(0));

        m4Tmp[2][3] = static_cast<T>(-1.0);
        m4Tmp[3][2] = static_cast<T>(-2.0 * zFar * zNear / zMinus);

        return m4Tmp;
    }
}

#endif //GM_TRANSFORM_H