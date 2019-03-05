#ifndef GEOMETRIC_H
#define GEOMETRIC_H

#include "vec4.hpp"
#include "quaternion.hpp"

#include "mat2x2.hpp"
#include "mat3x3.hpp"
#include "mat4x4.hpp"

namespace gm {

    template<typename T>
    T det(const gm_mat2<T> &m)
    {
        return m[0][0] * m[1][1] - m[1][0] * m[0][1];
    }

    template<typename T>
    T det(const gm_mat3<T> &m)
    {
        return   m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1])
               - m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0])
               + m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
    }

    template<typename T>
    T det(const gm_mat4<T> &m)
    {
        T SubFactor00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
        T SubFactor01 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
        T SubFactor02 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
        T SubFactor03 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
        T SubFactor04 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
        T SubFactor05 = m[2][0] * m[3][1] - m[3][0] * m[2][1];

        return   m[0][0] * (m[1][1] * SubFactor00 - m[1][2] * SubFactor01 + m[1][3] * SubFactor02)
               - m[0][1] * (m[1][0] * SubFactor00 - m[1][2] * SubFactor03 + m[1][3] * SubFactor04)
               + m[0][2] * (m[1][0] * SubFactor01 - m[1][1] * SubFactor03 + m[1][3] * SubFactor05)
               - m[0][3] * (m[1][0] * SubFactor02 - m[1][1] * SubFactor04 + m[1][2] * SubFactor05);
    }

    template<typename T>
    gm_mat2<T> inverse(const gm_mat2<T> &m)
    {
        T Determinant = det(m);

        return gm_mat2<T>(
                      m[1][1] / Determinant, - m[0][1] / Determinant,
                    - m[1][0] / Determinant,   m[0][0] / Determinant
               );
    }

    template<typename T>
    gm_mat3<T> inverse(const gm_mat3<T> &m)
    {
        T Determinant = det(m);

        return gm_mat3<T>(
                      (m[1][1] * m[2][2] - m[2][1] * m[1][2]) / Determinant,
                    - (m[1][0] * m[2][2] - m[2][0] * m[1][2]) / Determinant,
                      (m[1][0] * m[2][1] - m[2][0] * m[1][1]) / Determinant,
                    - (m[0][1] * m[2][2] - m[2][1] * m[0][2]) / Determinant,
                      (m[0][0] * m[2][2] - m[2][0] * m[0][2]) / Determinant,
                    - (m[0][0] * m[2][1] - m[2][0] * m[0][1]) / Determinant,
                      (m[0][1] * m[1][2] - m[1][1] * m[0][2]) / Determinant,
                    - (m[0][0] * m[1][2] - m[1][0] * m[0][2]) / Determinant,
                      (m[0][0] * m[1][1] - m[1][0] * m[0][1]) / Determinant
               );
    }

    template<typename T>
    gm_mat4<T> inverse(const gm_mat4<T> &m)
    {
        T SubFactor00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
        T SubFactor01 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
        T SubFactor02 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
        T SubFactor03 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
        T SubFactor04 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
        T SubFactor05 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
        T SubFactor06 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
        T SubFactor07 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
        T SubFactor08 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
        T SubFactor09 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
        T SubFactor10 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
        T SubFactor11 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
        T SubFactor12 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
        T SubFactor13 = m[1][2] * m[2][3] - m[2][2] * m[1][3];
        T SubFactor14 = m[1][1] * m[2][3] - m[2][1] * m[1][3];
        T SubFactor15 = m[1][1] * m[2][2] - m[2][1] * m[1][2];
        T SubFactor16 = m[1][0] * m[2][3] - m[2][0] * m[1][3];
        T SubFactor17 = m[1][0] * m[2][2] - m[2][0] * m[1][2];
        T SubFactor18 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

        gm_mat4<T> Inverse;
        Inverse[0][0] = + (m[1][1] * SubFactor00 - m[1][2] * SubFactor01 + m[1][3] * SubFactor02);
        Inverse[0][1] = - (m[1][0] * SubFactor00 - m[1][2] * SubFactor03 + m[1][3] * SubFactor04);
        Inverse[0][2] = + (m[1][0] * SubFactor01 - m[1][1] * SubFactor03 + m[1][3] * SubFactor05);
        Inverse[0][3] = - (m[1][0] * SubFactor02 - m[1][1] * SubFactor04 + m[1][2] * SubFactor05);

        Inverse[1][0] = - (m[0][1] * SubFactor00 - m[0][2] * SubFactor01 + m[0][3] * SubFactor02);
        Inverse[1][1] = + (m[0][0] * SubFactor00 - m[0][2] * SubFactor03 + m[0][3] * SubFactor04);
        Inverse[1][2] = - (m[0][0] * SubFactor01 - m[0][1] * SubFactor03 + m[0][3] * SubFactor05);
        Inverse[1][3] = + (m[0][0] * SubFactor02 - m[0][1] * SubFactor04 + m[0][2] * SubFactor05);

        Inverse[2][0] = + (m[0][1] * SubFactor06 - m[0][2] * SubFactor07 + m[0][3] * SubFactor08);
        Inverse[2][1] = - (m[0][0] * SubFactor06 - m[0][2] * SubFactor09 + m[0][3] * SubFactor10);
        Inverse[2][2] = + (m[0][0] * SubFactor11 - m[0][1] * SubFactor09 + m[0][3] * SubFactor12);
        Inverse[2][3] = - (m[0][0] * SubFactor08 - m[0][1] * SubFactor10 + m[0][2] * SubFactor12);

        Inverse[3][0] = - (m[0][1] * SubFactor13 - m[0][2] * SubFactor14 + m[0][3] * SubFactor15);
        Inverse[3][1] = + (m[0][0] * SubFactor13 - m[0][2] * SubFactor16 + m[0][3] * SubFactor17);
        Inverse[3][2] = - (m[0][0] * SubFactor14 - m[0][1] * SubFactor16 + m[0][3] * SubFactor18);
        Inverse[3][3] = + (m[0][0] * SubFactor15 - m[0][1] * SubFactor17 + m[0][2] * SubFactor18);

        T Determinant =
            + m[0][0] * Inverse[0][0]
            + m[0][1] * Inverse[0][1]
            + m[0][2] * Inverse[0][2]
            + m[0][3] * Inverse[0][3];

        Inverse /= Determinant;

        return Inverse;
    }


    template<typename T>
    gm_mat4<T> translate(const gm_mat4<T> &m4, const gm_vec3<T> &v3) {
        gm_mat4<T> result(m4);
        result[3] = m4[0] * v3.x + m4[1] * v3.y + m4[2] * v3.z + m4[3]; 

        return result;
    }

    // the order of euler-angle is yaw、pitch、roll
    template<typename T>
    gm_mat4<T> rotate(const gm_mat4<T> &m4, const T angle, const gm_vec3<T> &v3) {
        T a = radians(angle);
		T const c = cos(a);
		T const s = sin(a);

		gm_vec3<T> axis(normalize(v3));
		gm_vec3<T> temp((T(1) - c) * axis);
	    gm_mat4<T> rotate;
		rotate[0][0] = c + temp[0] * axis[0];
		rotate[0][1] = temp[0] * axis[1] + s * axis[2];
		rotate[0][2] = temp[0] * axis[2] - s * axis[1];

		rotate[1][0] = temp[1] * axis[0] - s * axis[2];
		rotate[1][1] = c + temp[1] * axis[1];
		rotate[1][2] = temp[1] * axis[2] + s * axis[0];

		rotate[2][0] = temp[2] * axis[0] + s * axis[1];
		rotate[2][1] = temp[2] * axis[1] - s * axis[0];
		rotate[2][2] = c + temp[2] * axis[2];

        gm_mat4<T> result;
		result[0] = m4[0] * rotate[0][0] + m4[1] * rotate[0][1] + m4[2] * rotate[0][2];
		result[1] = m4[0] * rotate[1][0] + m4[1] * rotate[1][1] + m4[2] * rotate[1][2];
		result[2] = m4[0] * rotate[2][0] + m4[1] * rotate[2][1] + m4[2] * rotate[2][2];
		result[3] = m4[3];

		return result;
    }

    template<typename T>
    gm_mat4<T> scale(const gm_mat4<T> &m4, const gm_vec3<T> &v3) {
        gm_mat4<T> result;
        result[0] = m4[0] * v3.x;
        result[1] = m4[1] * v3.y;
        result[2] = m4[2] * v3.z;
        result[3] = m4[3];

        return result;
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
    gm_mat4<T> ortho(const T yFov, const T aspect, const T zNear, const T zFar) {
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
#endif // GEOMETRIC_H
