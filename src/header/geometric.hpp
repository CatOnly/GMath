#ifndef GEOMETRIC_H
#define GEOMETRIC_H

#include "vec4.hpp"
#include "mat3x3.hpp"
#include "mat4x4.hpp"
#include "operator.hpp"

namespace SFL {

    // -- tools -------------------------
    template<typename T>
    const T *valuePtrFrom(const sfl_mat3<T> &vector) {
        return &(vector[0][0]);
    }

    template<typename T>
    const T *valuePtrFrom(const sfl_mat4<T> &vector) {
        return &(vector[0][0]);
    }

    // -- base functions ----------------
    template<typename T>
    T length(const sfl_vec3<T> &vector){
        return sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
    }

    template<typename T>
    T length(const sfl_vec4<T> &vector){
        return sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z + vector.w * vector.w);
    }

    template<typename T>
    T dot(const sfl_vec3<T> &vectorL, const sfl_vec3<T> &vectorR) {
        return vectorL.x * vectorR.x + vectorL.y * vectorR.y + vectorL.z * vectorR.z;
    }

    template<typename T>
    T dot(const sfl_vec4<T> &vectorL, const sfl_vec4<T> &vectorR) {
        return vectorL.x * vectorR.x + vectorL.y * vectorR.y + vectorL.z * vectorR.z + vectorL.w * vectorR.w;
    }

    template<typename T>
    sfl_vec3<T> cross(const sfl_vec3<T> &vectorL, const sfl_vec3<T> &vectorR) {
        return sfl_vec3<T>(
            vectorL.y * vectorR.z - vectorL.z * vectorR.y,
            vectorL.z * vectorR.x - vectorL.x * vectorR.z,
            vectorL.x * vectorR.y - vectorL.y * vectorR.x
        );
    }

    template<typename T>
    sfl_vec3<T> normalize(const sfl_vec3<T> &vector) {
        T avg = length(vector);
        return sfl_vec3<T>(vector.x/avg, vector.y/avg, vector.z/avg);
    }

    template<typename T>
    sfl_vec4<T> normalize(const sfl_vec4<T> &vector) {
        T avg = vector.length();
        return sfl_vec4<T>(vector.x/avg, vector.y/avg, vector.z/avg, vector.w/avg);
    }

    // -- transform functions ----------------
    template<typename T>
    sfl_mat4<T> translate(const sfl_mat4<T> &matrix4, const sfl_vec3<T> &vector3) {
        sfl_mat4<T> m4Tmp(matrix4);

        m4Tmp[0] = matrix4[0];
        m4Tmp[1] = matrix4[1];
        m4Tmp[2] = matrix4[2];

        return m4Tmp;
    }

    template<typename T>
    sfl_mat4<T> rotate(const sfl_mat4<T> &matrix4, const T, const sfl_vec3<T> &vector3) {
        sfl_mat4<T> m4Tmp(matrix4);


        return m4Tmp;
    }

    template<typename T>
    sfl_mat4<T> scale(const sfl_mat4<T> &matrix4, const sfl_vec3<T> &vector3) {
        sfl_mat4<T> m4Tmp(matrix4);
        m4Tmp[0][0] *= vector3.x;
        m4Tmp[1][1] *= vector3.y;
        m4Tmp[2][2] *= vector3.z;

        return m4Tmp;
    }

    template<typename T>
    sfl_mat4<T> perspective(const double yFov, const double aspect, const double zNear, const double zFar) {
        double top    = tan(yFov * 0.5 * ANGLE_TO_RADIAN) * zNear;
        double right  = -top * aspect;
        double zMinus = zFar - zNear;

        sfl_mat4<T> m4Tmp(static_cast<T>(zNear / right),
                          static_cast<T>(zNear / top),
                          static_cast<T>(-(zFar + zNear) / zMinus),
                          static_cast<T>(0));

        m4Tmp[2][3] = static_cast<T>(-1.0);
        m4Tmp[3][2] = static_cast<T>(-2.0 * zFar * zNear / zMinus);

        return m4Tmp;
    }
}
#endif // GEOMETRIC_H
