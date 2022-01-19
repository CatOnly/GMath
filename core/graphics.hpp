#ifndef GM_GRPAH_H
#define GM_GRPAH_H

#include "geometric.hpp"

namespace gm {

    // For aces filmic tone mapping curve, see
    // https://knarkowicz.wordpress.com/2016/01/06/aces-filmic-tone-mapping-curve/
    inline float aces(float value) {
       float a = 2.51f;
       float b = 0.03f;
       float c = 2.43f;
       float d = 0.59f;
       float e = 0.14f;
       return GM_CLAMP((value * (a * value + b)) / (value * (c * value + d) + e), 0.0f, 1.0f);
    }
    
   /*
    * By Vector's cross dot start-end and start-vector
    * Note the world coordinate is left hand or right hand)
    * Here is Right Hand, so return:
    * val > 0 is inside
    * val = 0 is on edge
    * val < 0 is outside
    * For more details see:
    * https://www.scratchapixel.com/lessons/3d-basic-rendering/rasterization-practical-implementation/rasterization-stage
    */
    template <typename T>
    T whichSideOfEdge(gm_vec2<T> s, gm_vec2<T> e, gm_vec2<T> v) {
        return (v.x - s.x) * (e.y - s.y) - (v.y - s.y) * (e.x - s.x);
    }


   /*
    * Coordinate: Right hand
    *
    * From Cartesian's coordinate to trangle's barycentric
    */
    template <typename T>
    gm_vec3<T> barycentric(const gm_vec4<T>& p1, const gm_vec4<T>& p2, const gm_vec4<T>& p3, const gm_vec2<T>& p)
    {
        gm_vec3<T> s[2];
        for (int i = 2; i--;)
        {
            s[i][0] = p2[i] - p1[i];
            s[i][1] = p3[i] - p1[i];
            s[i][2] = p1[i] -  p[i];
        }

        gm_vec3<T> u = cross(s[0], s[1]);
        if (GM_ABS(u.z) == 0) return gm_vec3<T>(-1, 1, 1);

        return gm_vec3<T>(1.f - (u.x + u.y) / u.z, u.x / u.z, u.y / u.z);
    }

   /*
    * Coordinate: Right hand
    *
    *  x_axis.x         y_axis.x         z_axis.x           0
    *  x_axis.y         y_axis.y         y_axis.y           0
    *  x_axis.z         y_axis.z         z_axis.z           0
    * -dot(x_axis,eye) -dot(y_axis,eye) -dot(z_axis,eye)    1
    */
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

#if GM_IS_Z_SCORPE_0_TO_1 > 0

    /*
     * Coordinate: Right hand
     * Scope: x[-1,1]  y[-1,1]  z[ 0,1]
     *
     * n/r    0        0            0
     *   0  n/t        0            0
     *   0    0  f/(f-n) -2*f*n/(f-n)
     *   0    0        1            0
     */
    template<typename T>
    gm_mat4<T> perspective(const T yHalfFov, const T width, const T height, const T zNear, const T zFar)
    {
		T top = static_cast<T>(tan(GM_RADIANS(yHalfFov / static_cast<T>(2)))) * zNear;
		T right = top * width / height;
		T zScope = zFar - zNear;

		gm_mat4<T> m4(
			zNear / right,
			zNear / top,
			zFar / zScope,
			static_cast<T>(0)
		);

		m4[2][3] = static_cast<T>(1);
		m4[3][2] = -zFar * zNear / zScope;

		return m4;
	}

#else

    /*
     * Coordinate: Right hand
     * Scope: x[-1,1]  y[-1,1]  z[-1,1]
     *
     * n/r    0            0    0
     *   0  n/t            0    0
     *   0    0  -(f+n)/(f-n)  -1
     *   0    0  -2*f*n/(f-n)   0
     */
    template<typename T>
    gm_mat4<T> perspective(const T yHalfFov, const T width, const T height, const T zNear, const T zFar) {
        T tanHalfFovY = static_cast<T>(tan(GM_RADIANS(yHalfFov / static_cast<T>(2))));
        T zNegScope = zNear - zFar;

        gm_mat4<T> m4(
            static_cast<T>(1) / (tanHalfFovY * width / height),
            static_cast<T>(1) / tanHalfFovY,
            (zFar + zNear) / zNegScope,
            static_cast<T>(0)
        );

        m4[2][3] = static_cast<T>(-1);
        m4[3][2] = (static_cast<T>(2) * zFar * zNear) / zNegScope;

        return m4;
    }

#endif

   /*
    * Coordinate: Right hand
    *
    * 1/r    0            0    0
    *   0  1/t            0    0
    *   0    0      -2/(f-n)   0
    *   0    0  -(f+n)/(f-n)   1
    */
    template<typename T>
    gm_mat4<T> ortho(const T yHalfFov, const T width, const T height, const T zNear, const T zFar) {
        T top    = static_cast<T>((GM_RADIANS(yHalfFov / static_cast<T>(2)))) * zNear;
        T right  = top * width / height;
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

#endif /* GM_GRPAH_H */
