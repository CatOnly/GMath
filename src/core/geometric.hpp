#ifndef GEOMETRIC_H
#define GEOMETRIC_H

#include "vec4.hpp"
#include "quaternion.hpp"

#include "mat2x2.hpp"
#include "mat3x3.hpp"
#include "mat4x4.hpp"

// PI / 180.0
#define GM_ANGLE_TO_RADIAN 0.017453

namespace gm {    
    
    template<typename T>
    T radians(const T angle){
        return angle * static_cast<T>(GM_ANGLE_TO_RADIAN);
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
