#ifndef GM_QUATERNION_H
#define GM_QUATERNION_H

#include "vec3.hpp"
#include "mat3x3.hpp"

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
    return gm_quaternion<T>(static_cast<T>(value) symbol v.x, static_cast<T>(value) symbol v.y, static_cast<T>(value) symbol v.z, static_cast<T>(value) symbol v.w);\
}

namespace gm {

    template<typename T> class gm_mat4;
    template <typename T> class gm_quaternion
    {
    public:
        T x, y, z, w;

        gm_quaternion():x(static_cast<T>(0)),y(static_cast<T>(0)),z(static_cast<T>(0)),w(static_cast<T>(1)){}
        gm_quaternion(T x, T y, T z, T w):x(static_cast<T>(x)),y(static_cast<T>(y)),z(static_cast<T>(z)),w(static_cast<T>(w)){}
        gm_quaternion(const T& pitch, const T& yaw, const T& roll) 
        {
            gm_vec3<T> eulerAngle(pitch * T(0.5), yaw * T(0.5), roll * T(0.5));
            gm_vec3<T> c = gm::cos(eulerAngle * T(0.5));
            gm_vec3<T> s = gm::sin(eulerAngle * T(0.5));
            
            this->w = c.x * c.y * c.z + s.x * s.y * s.z;
            this->x = s.x * c.y * c.z - c.x * s.y * s.z;
            this->y = c.x * s.y * c.z + s.x * c.y * s.z;
            this->z = c.x * c.y * s.z - s.x * s.y * c.z;
        }
        
        gm_quaternion(const gm_quaternion<T> &v):gm_quaternion(v.x, v.y, v.z, v.w){}

        explicit gm_quaternion(gm_vec3<T> axis, const T &theta) {
            if (fabs(1.0f - dot(axis, axis)) > 0.01f) {
                axis = normalize(axis);
            }

            float thetaHalf = float(radians(theta / 2));
            float sinThetaHalf = sin(thetaHalf);

            x = axis.x * sinThetaHalf;
            y = axis.y * sinThetaHalf;
            z = axis.z * sinThetaHalf;
            w = cos(thetaHalf);
        }

        explicit gm_quaternion(const gm_mat3<T>& m);
		explicit gm_quaternion(const gm_mat4<T>& m);

        T length(const gm_quaternion<T> &q) const {
            return std::sqrt(dot(q));
        }

        gm_quaternion<T> normalize() const {
            T avg = length();
            bool isNoZero = avg != static_cast<T>(0);
            GM_ASSERT(isNoZero);

            return isNoZero ? gm_quaternion<T>(x/avg, y/avg, z/avg, w/avg) : gm_quaternion<T>();
        }

        gm_quaternion<T> normalize(const gm_quaternion<T> &q) const {
            T len = length(q);
            if(len <= T(0)) return gm_quaternion<T>(1, 0, 0, 0);

            T oneOverLen = T(1) / len;
            return gm_quaternion<T>(q.w * oneOverLen, q.x * oneOverLen, q.y * oneOverLen, q.z * oneOverLen);
        }

        T dot(const gm_quaternion<T> &v) const {
            return x * v.x + y * v.y + z * v.z + w * v.w;
        }

        gm_quaternion<T> cross(const gm_quaternion<T> &v) const {
            return gm_quaternion<T>(
                w * q.w - x * q.x - y * q.y - z * q.z,
                w * q.x + x * q.w + y * q.z - z * q.y,
                w * q.y + y * q.w + z * q.x - x * q.z,
                w * q.z + z * q.w + x * q.y - y * q.x
            );
        }

        gm_quaternion<T> conjugate() const {
            return gm_quaternion<T>(w, -x, -y, -z);
        }

        gm_quaternion<T> inverse() const {
            return conjugate() / dot(*this);
        }

        gm_quaternion<T> rotate(const gm_vec3<T> v, T angle) const {
            gm_vec3<T> Tmp = v;

            // Axis of rotation must be normalised
            T len = Tmp.length();
            if(GM_ABS(len - T(1)) > T(gm::EPS))
            {
                T oneOverLen = T(1) / len;
                Tmp.x *= oneOverLen;
                Tmp.y *= oneOverLen;
                Tmp.z *= oneOverLen;
            }

            T AngleRad = GM_RADIANS(angle);
            T fSin = std::sin(AngleRad * T(0.5));

            return q * gm_quaternion<T>(std::cos(AngleRad * T(0.5)), Tmp.x * fSin, Tmp.y * fSin, Tmp.z * fSin);
        }

        gm_vec3<T> euler() const {
            T h;
            T p = gm::asin(-2.0f * (y * z + w * x));
            T r = T(0);

            T cosP = std::cos(p);
            if (cosP != T(0)) {
                h = std::atan2(x * z - w * y, 0.5f - x * x - y * y);
                r = std::atan2(x * y - w * z, 0.5f - x * x - z * z);
            } else {
                h = std::atan2(-x * z - w * y, 0.5f - y * y - z * z);
            }
            
            return gm_vec3<T>(h, p, r);
        }

        gm_mat4<T> mat3() const;
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
                x == static_cast<T>(0) ? x : -x, 
                y == static_cast<T>(0) ? y : -y,
                z == static_cast<T>(0) ? z : -z,
                w == static_cast<T>(0) ? w : -w
            );        
        }

        gm_quaternion<T> operator / (const T &value) {
            GM_ASSERT(value != static_cast<T>(0));
            gm_quaternion<T> v;
            v.x = x / value;
            v.y = y / value;
            v.z = z / value;
            v.w = w / value;

            return v;
        }

        gm_quaternion<T>& operator /= (const T &value) {
            GM_ASSERT(value != static_cast<T>(0));
            x /= value;
            y /= value;
            z /= value;
            w /= value;

            return *this;
        }

        gm_quaternion<T> operator * (const gm_quaternion<T> &q) const {
            return gm_quaternion<T>(
                w*q.x + x*q.w + y*q.z - z*q.y,
                w*q.y + y*q.w + z*q.x - x*q.z,
                w*q.z + z*q.w + x*q.y - y*q.x,
                w*q.w - x*q.x - y*q.y - z*q.z
            );
        }

        gm_quaternion<T>& operator *= (const gm_quaternion<T> &q) {
            *this = *this * q;

            return *this;
        }
        
        bool operator==(const gm_quaternion<T>& q) const
        {
            return (q.x == x && q.y == y && q.z == z && q.w == w);
        }
    };

    GM_Q_OPERATOR_NUM_RIGHT(+)
    GM_Q_OPERATOR_NUM_RIGHT(-)
    GM_Q_OPERATOR_NUM_RIGHT(*)

    template<typename T>
    gm_quaternion<T> operator / (const T &value, const gm_quaternion<T> &v)
    {
        GM_ASSERT(v.x != static_cast<T>(0) && v.y != static_cast<T>(0) && v.z != static_cast<T>(0) && v.w != static_cast<T>(0));
        return gm_quaternion<T>(static_cast<T>(value) / v.x, static_cast<T>(value) / v.y, static_cast<T>(value) / v.z, static_cast<T>(value) / v.w);
    }

    template<typename T>
    gm_vec3<T> operator * (const gm_quaternion<T> &q, const gm_vec3<T> &v) 
    {
        T two(2);
        gm_vec3<T> uv, uuv;
		gm_vec3<T> vq(q.x, q.y, q.z);
		uv = vq.cross(v);
		uuv = vq.cross(uv);
		uv *= (Two * q.w); 
		uuv *= Two; 

		return v + uv + uuv;
    }

    template<typename T>
    gm_vec3<T> operator * (const gm_vec3<T> &v, const gm_quaternion<T> &q)
    {
        return q.inverse() * v;
    }

    template<typename T>
    gm_vec4<T> operator * (const gm_quaternion<T> &q, const gm_vec4<T> &v);

    template<typename T>
    gm_vec4<T> operator * (const gm_vec4<T> &v, const gm_quaternion<T> &q); 

    template<typename T>
    std::ostream& operator << (std::ostream &os, const gm_quaternion<T> &v)
    {
        using namespace std;
        os << setprecision(GM_OUTPUT_PRECISION)
           << setw(GM_OUTPUT_WIDTH)
           << GM_OUTPUT_POINT_CMD << GM_OUTPUT_FIXED_CMD
           <<"[(" << v.x << ", " << v.y << ", " << v.z << "), " << v.w << "] ";

        return os;
    }

} // namespace gm

// #include "quaternion.inl"

#endif //GM_QUATERNION_H
