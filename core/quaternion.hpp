#ifndef GM_QUATERNION_H
#define GM_QUATERNION_H

#include "common.hpp"

#define GM_Q_OPERATOR_BASE(symbol) \
gm_quaternion<T> operator symbol (const gm_quaternion<T> &a){\
    return gm_quaternion<T>(x symbol a.x, y symbol a.y, z symbol a.z, w symbol a.w);\
}

#define GM_Q_OPERATOR_NUM_LEFT(symbol)\
gm_quaternion<T> operator symbol (const T &value){\
    gm_quaternion<T> v;\
    v.x = x symbol value;\
    v.y = y symbol value;\
    v.z = z symbol value;\
    v.w = w symbol value;\
\
    return v;\
}


#define GM_Q_OPERATOR_SELF_NUM_LEFT(symbol)\
gm_quaternion<T>& operator symbol (const T &value){\
    x symbol value;\
    y symbol value;\
    z symbol value;\
    w symbol value;\
\
    return *this;\
}

#define GM_Q_OPERATOR_NUM_RIGHT(symbol)\
template<typename T> \
gm_quaternion<T> operator symbol (const T &value, const gm_quaternion<T> &v){\
    return gm_quaternion<T>(T(value) symbol v.x, T(value) symbol v.y, T(value) symbol v.z, T(value) symbol v.w);\
}

namespace gm {

    template <typename T> class gm_quaternion
    {
    public:
        T x, y, z, w;

        gm_quaternion() : x(T(0)),y(T(0)),z(T(0)),w(T(1)){}
        gm_quaternion(T x, T y, T z, T w) : x(T(x)),y(T(y)),z(T(z)),w(T(w)){}
        gm_quaternion(const gm_quaternion<T> &v):gm_quaternion(v.x, v.y, v.z, v.w){}

        explicit gm_quaternion(gm_vec3<T> axis, const T &theta);

        // Eular Order: ZYX
		explicit gm_quaternion(const T& pitch, const T& yaw, const T& roll);
        explicit gm_quaternion(const gm_mat3<T>& m);
		explicit gm_quaternion(const gm_mat4<T>& m);

		T length(const gm_quaternion<T> &q) const;

		gm_quaternion<T> normalize() const;
		gm_quaternion<T> normalize(const gm_quaternion<T> &q) const;

		T dot(const gm_quaternion<T> &v) const;

        // q^*
		gm_quaternion<T> conjugate() const;
        // q^-1
		gm_quaternion<T> inverse() const;

        // Eular Order: ZYX
		T pitch() const;
        
        // Eular Order: ZYX
		T yaw() const;
        
        // Eular Order: ZYX
        T roll() const;

        gm_mat3<T> mat3() const;
        gm_mat4<T> mat4() const;

        GM_Q_OPERATOR_BASE(+)
        GM_Q_OPERATOR_BASE(-)

        GM_Q_OPERATOR_NUM_LEFT(+)
        GM_Q_OPERATOR_NUM_LEFT(-)
        GM_Q_OPERATOR_NUM_LEFT(*)

        GM_Q_OPERATOR_SELF_NUM_LEFT(+=)
        GM_Q_OPERATOR_SELF_NUM_LEFT(-=)
        GM_Q_OPERATOR_SELF_NUM_LEFT(*=)

        gm_quaternion<T> operator - () const {
            return gm_quaternion<T>(
                x == T(0) ? x : -x, 
                y == T(0) ? y : -y,
                z == T(0) ? z : -z,
                w == T(0) ? w : -w
            );        
        }

        gm_quaternion<T> operator / (const T &value) {
            GM_ASSERT(value != T(0));
            gm_quaternion<T> v;
            v.x = x / value;
            v.y = y / value;
            v.z = z / value;
            v.w = w / value;

            return v;
        }

        gm_quaternion<T>& operator /= (const T &value) {
            GM_ASSERT(value != T(0));
            x /= value;
            y /= value;
            z /= value;
            w /= value;

            return *this;
        }

		gm_quaternion<T> operator * (const gm_quaternion<T> &q) const;
        gm_quaternion<T>& operator *= (const gm_quaternion<T> &q) {
            *this = *this * q;

            return *this;
        }
        
        bool operator==(const gm_quaternion<T>& q) const
        {
            return (q.x == x && q.y == y && q.z == z && q.w == w);
        }
    };

	// Operations	------------------------------

    GM_Q_OPERATOR_NUM_RIGHT(+)
    GM_Q_OPERATOR_NUM_RIGHT(-)
    GM_Q_OPERATOR_NUM_RIGHT(*)

    template<typename T>
    gm_quaternion<T> operator / (const T &value, const gm_quaternion<T> &v)
    {
        GM_ASSERT(v.x != T(0) && v.y != T(0) && v.z != T(0) && v.w != T(0));
        return gm_quaternion<T>(T(value) / v.x, T(value) / v.y, T(value) / v.z, T(value) / v.w);
    }

	template<typename T>
	std::ostream& operator << (std::ostream &os, const gm_quaternion<T> &v)
	{
		using namespace std;
		os << setprecision(GM_OUTPUT_PRECISION)
			<< setw(GM_OUTPUT_WIDTH)
			<< GM_OUTPUT_POINT_CMD << GM_OUTPUT_FIXED_CMD
			<< "[(" << v.x << ", " << v.y << ", " << v.z << "), " << v.w << "] ";

		return os;
	}

    // q.xyz is an unit vector3
    // q * v = q * v * q^*
    template<typename T>
	gm_vec3<T> operator * (const gm_quaternion<T> &q, const gm_vec3<T> &v);

    template<typename T>
	gm_vec3<T> operator * (const gm_vec3<T> &v, const gm_quaternion<T> &q);

    template<typename T>
    gm_vec4<T> operator * (const gm_quaternion<T> &q, const gm_vec4<T> &v);

    template<typename T>
    gm_vec4<T> operator * (const gm_vec4<T> &v, const gm_quaternion<T> &q); 

	template<typename T>
	gm_quaternion<T> pow(const gm_quaternion<T> &q, float exponent);

	// Interpolation	------------------------------

	template<typename T>
	gm_quaternion<T> lerp(const gm_quaternion<T> &q0, const gm_quaternion<T> &q1, float t);

	template<typename T>
	gm_quaternion<T> nlerp(const gm_quaternion<T> &q0, const gm_quaternion<T> &q1, float t);

	template<typename T>
	gm_quaternion<T> slerp(const gm_quaternion<T> &q0, const gm_quaternion<T> &q1, float t);

} // namespace gm

#include "quaternion.inl"

#endif //GM_QUATERNION_H
