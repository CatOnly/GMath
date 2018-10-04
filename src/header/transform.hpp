#ifndef GM_TRANSFORM_H
#define GM_TRANSFORM_H

#include "quaternion.hpp"
#include "geometric.hpp"
#include <iostream>

// PI / 180.0
#define GM_ANGLE_TO_RADIAN 0.017453

namespace gm {

    // -- tools -----------------------------
    template<typename T>
    T radians(const T angle){
        return angle * static_cast<T>(GM_ANGLE_TO_RADIAN);
    }

    template<typename T>
    const T *valuePtrFrom(const gm_mat3<T> &m3) {
        return &(m3[0][0]);
    }

    template<typename T>
    const T *valuePtrFrom(const gm_mat4<T> &m4) {
        return &(m4[0][0]);
    }

    // -- transform --------------------------
    template<typename T>
    gm_mat4<T> translate(const gm_mat4<T> &m4Origin, const gm_vec3<T> &v3) {
        gm_mat4<T> m4;
        m4[3][0] = v3.x;
        m4[3][1] = v3.y;
        m4[3][2] = v3.z;

        return m4 * m4Origin;
    }

    // the order of euler-angle is yaw、pitch、roll
    template<typename T>
    gm_mat4<T> rotate(const gm_mat4<T> &m4Origin, const T angle, const gm_vec3<T> &v3Axis) {
        T radio = radians(angle);

#ifndef GM_USE_COORDINATE_LEFTHAND
        gm_mat4<T> m4;
#else
        gm_mat4<T> m4;
#endif

        return m4 * m4Origin;
    }

    template<typename T>
    gm_mat4<T> scale(const gm_mat4<T> &m4Origin, const gm_vec3<T> &v3) {
        return gm_mat4<T>(v3.x, v3.y, v3.z, 1) * m4Origin;
    }

    template<typename T>
    gm_mat4<T> lookAt(const gm_vec3<T> &v3PosEye, const gm_vec3<T> &v3PosTarget, const gm_vec3<T> &v3Up) {
        gm_vec3<T> v3EyeNegDir = normalize(v3PosEye - v3PosTarget);
        gm_vec3<T> v3EyeNegRight = normalize(cross(v3Up, v3EyeNegDir));
        gm_vec3<T> v3EyeUp = normalize(cross(v3EyeNegDir, v3EyeNegRight));

        gm_mat4<T> m4;

        m4[0][0] = v3EyeNegRight.x;
        m4[1][0] = v3EyeNegRight.y;
        m4[2][0] = v3EyeNegRight.z;

        m4[0][1] = v3EyeUp.x;
        m4[1][1] = v3EyeUp.y;
        m4[2][1] = v3EyeUp.z;

        m4[0][2] = v3EyeNegDir.x;
        m4[1][2] = v3EyeNegDir.y;
        m4[2][2] = v3EyeNegDir.z;

        m4[3][0] = dot(v3EyeNegRight, -v3PosEye);
        m4[3][1] = dot(v3EyeUp, -v3PosEye);
        m4[3][2] = dot(v3EyeNegDir, -v3PosEye);

        return m4;
    }

    template<typename T>
    gm_mat4<T> perspective(const T yFov, const T aspect, const T zNear, const T zFar) {
        T tanHalfFovY = static_cast<T>(tan(radians(yFov / static_cast<T>(2))));
        T zNegScope = zNear - zFar;

        gm_mat4<T> m4(
            static_cast<T>(1) / (tanHalfFovY * aspect),
            static_cast<T>(1) / tanHalfFovY,
            (zFar + zNear) / zNegScope,
            static_cast<T>(0)
        );

        m4[2][3] = static_cast<T>(-1);
        m4[3][2] = (static_cast<T>(2) * zFar * zNear) / zNegScope;

        return m4;
    }

    template<typename T>
    gm_mat4<T> orthogonal(const T yFov, const T aspect, const T zNear, const T zFar) {
        T top    = static_cast<T>((radians(yFov / static_cast<T>(2)))) * zNear;
        T right  = top * aspect;
        T zNegScope = zNear - zFar;

        gm_mat4<T> m4(
            static_cast<T>(1) / right,
            static_cast<T>(1) / top,
            static_cast<T>(2) / zNegScope,
            static_cast<T>(1)
        );

        m4[3][2] = (zFar + zNear) / zNegScope;

        return m4;
    }
}

#endif //GM_TRANSFORM_H
