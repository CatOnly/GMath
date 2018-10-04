#ifndef GM_TRANSFORM_H
#define GM_TRANSFORM_H

#include "quaternion.hpp"
#include "geometric.hpp"

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
        gm_mat4<T> m4(1);
#else
        gm_mat4<T> m4(1);
#endif

        return m4 * m4Origin;
    }

    template<typename T>
    gm_mat4<T> scale(const gm_mat4<T> &m4Origin, const gm_vec3<T> &v3) {
        return gm_mat4<T>(v3.x, v3.y, v3.z, 1) * m4Origin;
    }

    template<typename T>
    gm_mat4<T> lookAt(const gm_vec3<T> &v3PosCamera, const gm_vec3<T> &v3PosTarget, const gm_vec3<T> &v3Up) {
        gm_vec3<T> v3CameraNegDir = normalize(v3PosCamera - v3PosTarget);
        gm_vec3<T> v3CameraNegRight = normalize(cross(v3Up, v3CameraNegDir));
        gm_vec3<T> v3CameraUp = normalize(cross(v3CameraNegDir, v3CameraNegRight));
        gm_mat4<T> m4(
            gm_vec4<T>(v3CameraNegRight),
            gm_vec4<T>(v3CameraUp),
            gm_vec4<T>(v3CameraNegDir),
            gm_vec4<T>(0,0,0,1)
        );

        return translate(m4, v3PosCamera);
    }

    template<typename T>
    gm_mat4<T> perspective(const T yFov, const T aspect, const T zNear, const T zFar) {
        double top    = tan(radians(double(yFov) * 0.5)) * double(zNear);
        double right  = -top * aspect;
        double zNegScope = zNear - zFar;

        gm_mat4<T> m4(
            static_cast<T>(zNear / right),
            static_cast<T>(zNear / top),
            static_cast<T>((zFar + zNear) / zNegScope),
            static_cast<T>(0)
        );

        m4[2][3] = static_cast<T>(-1);
        m4[3][2] = static_cast<T>(2.0 * zFar * zNear / zNegScope);

        return m4;
    }

    template<typename T>
    gm_mat4<T> orthogonal(const T yFov, const T aspect, const T zNear, const T zFar) {
        double top    = tan(radians(double(yFov) * 0.5)) * double(zNear);
        double right  = -top * aspect;
        double zNegScope = zNear - zFar;

        gm_mat4<T> m4(
            static_cast<T>(1.0 / right),
            static_cast<T>(1.0 / top),
            static_cast<T>(2.0 / zNegScope),
            static_cast<T>(1)
        );

        m4[3][2] = static_cast<T>((zFar + zNear) / zNegScope);

        return m4;
    }
}

#endif //GM_TRANSFORM_H