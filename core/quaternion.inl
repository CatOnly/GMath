#include "mat4x4.hpp"

namespace gm {

	// Data		 ------------------------------

    template <typename T>
    gm_quaternion<T>::gm_quaternion(gm_vec3<T> axis, const T &theta)
    {
        if (fabs(1.0f - axis.dot(axis)) > 0.01f) {
            axis = axis.normalize();
        }

        float thetaHalf = float(GM_ANGLES(theta / 2));
        float sinThetaHalf = gm::sin(thetaHalf);

        x = axis.x * sinThetaHalf;
        y = axis.y * sinThetaHalf;
        z = axis.z * sinThetaHalf;
        w = gm::cos(thetaHalf);
    }
    
	template <typename T>
	gm_quaternion<T>::gm_quaternion(const T& pitch, const T& yaw, const T& roll)
	{
		gm_vec3<T> eulerAngle(pitch * T(0.5), yaw * T(0.5), roll * T(0.5));
		gm_vec3<T> c = gm::cos(eulerAngle);
		gm_vec3<T> s = gm::sin(eulerAngle);
        
		w = c.x * c.y * c.z + s.x * s.y * s.z;
		x = s.x * c.y * c.z - c.x * s.y * s.z;
		y = c.x * s.y * c.z + s.x * c.y * s.z;
		z = c.x * c.y * s.z - s.x * s.y * c.z;
	}

    template <typename T>
    gm_quaternion<T>::gm_quaternion(const gm_mat3<T>& m)
    {
        T fourXSquaredMinus1 = m[0][0] - m[1][1] - m[2][2];
        T fourYSquaredMinus1 = m[1][1] - m[0][0] - m[2][2];
        T fourZSquaredMinus1 = m[2][2] - m[0][0] - m[1][1];
        T fourWSquaredMinus1 = m[0][0] + m[1][1] + m[2][2];
        
        int biggestIndex = 0;
        T fourBiggestSquaredMinus1 = fourWSquaredMinus1;
        if(fourXSquaredMinus1 > fourBiggestSquaredMinus1)
        {
            fourBiggestSquaredMinus1 = fourXSquaredMinus1;
            biggestIndex = 1;
        }
        if(fourYSquaredMinus1 > fourBiggestSquaredMinus1)
        {
            fourBiggestSquaredMinus1 = fourYSquaredMinus1;
            biggestIndex = 2;
        }
        if(fourZSquaredMinus1 > fourBiggestSquaredMinus1)
        {
            fourBiggestSquaredMinus1 = fourZSquaredMinus1;
            biggestIndex = 3;
        }

        T biggestVal = gm::sqrt(fourBiggestSquaredMinus1 + T(1)) * T(0.5);
        T mult = T(0.25) / biggestVal;

        switch(biggestIndex)
        {
        case 0:
            w = biggestVal; 
            x = (m[1][2] - m[2][1]) * mult;
            y = (m[2][0] - m[0][2]) * mult;
            z = (m[0][1] - m[1][0]) * mult;
            break;
        case 1:
            w = (m[1][2] - m[2][1]) * mult;
            x = biggestVal;
            y = (m[0][1] + m[1][0]) * mult;
            z = (m[2][0] + m[0][2]) * mult;
            break;
        case 2:
            w = (m[2][0] - m[0][2]) * mult;
            x = (m[0][1] + m[1][0]) * mult;
            y = biggestVal;
            z = (m[1][2] + m[2][1]) * mult;
            break;
        case 3:
            w = (m[0][1] - m[1][0]) * mult;
            x = (m[2][0] + m[0][2]) * mult;
            y = (m[1][2] + m[2][1]) * mult;
            z = biggestVal;
            break;
        }
    }

    template <typename T>
	gm_quaternion<T>::gm_quaternion(const gm_mat4<T>& m)
    {
        gm_quaternion(gm_mat3<T>(m));
    }

    template <typename T>
    gm_mat3<T> gm_quaternion<T>::mat3() const
    {
        float xx = x * x;
        float xy = x * y;
        float xz = x * z;
        float xw = x * w;
        float yy = y * y;
        float yz = y * z;
        float yw = y * w;
        float zz = z * z;
        float zw = z * w;

        gm_mat3<T> m(1);

        m[0][0] = 1 - 2 * (yy + zz);
        m[0][1] = 2 * (xy - zw);
        m[0][2] = 2 * (xz + yw);

        m[1][0] = 2 * (xy + zw);
        m[1][1] = 1 - 2 * (xx + zz);
        m[1][2] = 2 * (yz - xw);

        m[2][0] = 2 * (xz - yw);
        m[2][1] = 2 * (yz + xw);
        m[2][2] = 1 - 2 * (xx + yy);

        return m;
    }

    template <typename T>
    gm_mat4<T> gm_quaternion<T>::mat4() const
    {
        return gm_mat4<T>(mat3());
    }

	template <typename T>
	gm_quaternion<T>  gm_quaternion<T>::operator * (const gm_quaternion<T> &q) const {
		return gm_quaternion<T>(
			w * q.x + x * q.w + y * q.z - z * q.y,
			w * q.y + y * q.w + z * q.x - x * q.z,
			w * q.z + z * q.w + x * q.y - y * q.x,
			w * q.w - x * q.x - y * q.y - z * q.z
        );
	}

	// Operators ------------------------------

    // Ref: https://people.csail.mit.edu/bkph/articles/Quaternions.pdf)
	template<typename T>
	gm_vec3<T> operator * (const gm_quaternion<T> &q, const gm_vec3<T> &v)
	{
        const gm_vec3<T> qu(q.x, q.y, q.z);
        const gm_vec3<T> qxv2 = T(2.0) * qu.cross(v);
        return v + (q.w * qxv2) + qu.cross(qxv2);
	}
	template<typename T>
	gm_vec3<T> operator * (const gm_vec3<T> &v, const gm_quaternion<T> &q)
	{
		return q.inverse() * v;
	}

	template<typename T>
	gm_vec4<T> operator * (const gm_quaternion<T> &q, const gm_vec4<T> &v)
	{
		return gm_vec4<T>(q * gm_vec3<T>(v), v.w);
	}
	template<typename T>
	gm_vec4<T> operator * (const gm_vec4<T> &v, const gm_quaternion<T> &q)
	{
		return q.inverse() * v;
	}

	// Function ------------------------------

	template <typename T>
	T gm_quaternion<T>::length(const gm_quaternion<T> &q) const 
	{
		return gm::sqrt(dot(q));
	}

	template <typename T>
	gm_quaternion<T> gm_quaternion<T>::normalize() const 
	{
		T avg = length();
		bool isNoZero = avg != T(0);
		GM_ASSERT(isNoZero);

		return isNoZero ? gm_quaternion<T>(x / avg, y / avg, z / avg, w / avg) : gm_quaternion<T>();
	}

	template <typename T>
	gm_quaternion<T> gm_quaternion<T>::normalize(const gm_quaternion<T> &q) const 
	{
		T len = length(q);
		if (len <= T(0)) return gm_quaternion<T>(1, 0, 0, 0);

		T oneOverLen = T(1) / len;
		return gm_quaternion<T>(q.w * oneOverLen, q.x * oneOverLen, q.y * oneOverLen, q.z * oneOverLen);
	}

	template<typename T>
	T gm_quaternion<T>::dot(const gm_quaternion<T> &v) const 
	{
		return x * v.x + y * v.y + z * v.z + w * v.w;
	}

	template<typename T>
	gm_quaternion<T> gm_quaternion<T>::conjugate() const 
	{
		return gm_quaternion<T>(w, -x, -y, -z);
	}

	template<typename T>
	gm_quaternion<T> gm_quaternion<T>::inverse() const 
	{
		return conjugate() / dot(*this);
	}

	template<typename T>
	T gm_quaternion<T>::pitch() const 
	{
		return GM_ANGLES(gm::atan2(T(2) * (y * z + w * x), w * w - x * x - y * y + z * z));
	}

	template<typename T>
	T gm_quaternion<T>::yaw() const 
	{
        return GM_ANGLES(gm::asin(T(-2) * (x * z - w * y)));
	}
    
    template<typename T>
    T gm_quaternion<T>::roll() const
    {
        return GM_ANGLES(gm::atan2(T(2) * (x * y + w * z), w * w + x * x - y * y - z * z));
    }

	template<typename T>
	gm_quaternion<T> pow(const gm_quaternion<T> &q, float exponent)
	{
		// This will protect against divide by zero
		if (fabs(q.w) > 1 - EPS) {
			return q;
		}

		float alpha = gm::acos(q.w);
		float newAlpha = alpha * exponent;
		float mult = gm::sin(newAlpha) / gm::sin(alpha);

		return gm_quaternion<T>(
			q.x * mult,
			q.y * mult,
			q.z * mult,
			gm::cos(newAlpha)
			);
	}

	// Interpolation	------------------------------

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
		}
		else {
			float sinTheta = gm::sqrt(1.0f - cosTheta * cosTheta);
			float theta = gm::atan2(sinTheta, cosTheta);
			float oneOverSinTheta = 1.0f / sinTheta;
			k0 = gm::sin((1.0f - t) * theta) * oneOverSinTheta;
			k1 = gm::sin(t * theta) * oneOverSinTheta;
		}

		return gm_quaternion<T>(T(k0) * q0 + T(k1) * q1);
	}

} // namespace gm 
