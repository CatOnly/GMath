#include "vec3.hpp"
#include "vec4.hpp"
#include "quaternion.hpp"

namespace gm {

    template<typename T>
    gm_vec3<T> sin(const gm_vec3<T> &v)
    {
        return gm_vec3<T>(
            std::sin(v.x),
            std::sin(v.y),
            std::sin(v.z)
        );
    }

    template<typename T>
    gm_vec3<T> cos(const gm_vec3<T> &v)
    {
        return gm_vec3<T>(
            std::cos(v.x),
            std::cos(v.y),
            std::cos(v.z)
        );
    }

    template<typename T>
    gm_quaternion<T> pow(const gm_quaternion<T> &q, float exponent)
    {
        // This will protect against divide by zero
        if (fabs(q.w) > 1 - EPS) {
            return q;
        }

        float alpha = std::acos(q.w);
        float newAlpha = alpha * exponent;
        float mult = std::sin(newAlpha) / std::sin(alpha);
        
        return gm_quaternion<T>(
            q.x * mult,
            q.y * mult,
            q.z * mult,
            std::cos(newAlpha)
        );
    }


    template<typename T>
    gm_quaternion<T> lerp(const gm_quaternion<T> &q0, const gm_quaternion<T> &q1, float t)
    {
        T angle = gm::acos(q0.dot(q1));
		return (gm::sin((T(1) - t) * angle) * q0 + gm::sin(t * angle) * q1) / gm::sin(angle);
    }

    template<typename T>
    gm_quaternion<T> nlerp(const gm_quaternion<T> &q0, const gm_quaternion<T> &q1, float t) 
    {
        return lerp(q0, q1, t).normalize();
    }

    // for spherical linear interpolation, see
    // 3D Math Primer for Graphics and Game Development, 2nd Edition, Chapter 8
	template<typename T>
	gm_quaternion<T> slerp(const gm_quaternion<T>& q0, const gm_quaternion<T>& q1, float t)
    {
        if (t <= 0.0f) return q0;
        if (t >= 1.0f) return q1;

        // Keep the shortest arc
        float cosTheta = float(q0.dot(q1));
        
        // q0 and q1 must be unit quaternions
        GM_ASSERT(cosTheta < 1.1f);

        if (cosTheta < 0.0f) {
            q1 = -q1;
            cosTheta = -cosTheta;
        }

        float k0, k1;
        if (cosTheta > 1 - gm::EPS) {
            // Very close - just use linear interpolation,
            // which will protect againt a divide by zero
            k0 = 1.0f - t;
            k1 = t;
        } else {
            float sinTheta = sqrt(1.0f - cosTheta*cosTheta);
            float theta = atan2(sinTheta, cosTheta);
            float oneOverSinTheta = 1.0f / sinTheta;
            k0 = gm::sin((1.0f - t) * theta) * oneOverSinTheta;
            k1 = gm::sin(t * theta) * oneOverSinTheta;
        }

        return gm_quaternion<T>(T(k0) * q0 + T(k1) * q1);
    }

} // namespace gm 