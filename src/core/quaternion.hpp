#ifndef GM_QUATERNION_H
#define GM_QUATERNION_H

#include "vec3.hpp"

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

    template <typename T> class gm_quaternion
    {
    public:
        T x, y, z, w;

        gm_quaternion():x(static_cast<T>(0)),y(static_cast<T>(0)),z(static_cast<T>(0)),w(static_cast<T>(0)){}
        gm_quaternion(T x, T y, T z, T w):x(static_cast<T>(x)),y(static_cast<T>(y)),z(static_cast<T>(z)),w(static_cast<T>(w)){}
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

        gm_quaternion<T> operator / (const T &value){
            GM_ASSERT(value != static_cast<T>(0));
            gm_quaternion<T> v;
            v.x = x / value;
            v.y = y / value;
            v.z = z / value;
            v.w = w / value;

            return v;
        }

        gm_quaternion<T>& operator /= (const T &value){
            GM_ASSERT(value != static_cast<T>(0));
            x /= value;
            y /= value;
            z /= value;
            w /= value;

            return *this;
        }

        gm_quaternion<T> operator * (const gm_quaternion<T> &q){
            return gm_quaternion<T>(
                w*q.x + x*q.w + y*q.z - z*q.y,
                w*q.y + y*q.w + z*q.x - x*q.z,
                w*q.z + z*q.w + x*q.y - y*q.x,
                w*q.w - x*q.x - y*q.y - z*q.z
            );
        }

        gm_quaternion<T>& operator *= (const gm_quaternion<T> &q){
            *this = *this * q;

            return *this;
        }

        gm_vec3<T> operator * (const gm_vec3<T> &v3) {
            gm_vec3<T> r3(x, y, z);
            T two = static_cast<T>(2);
            return gm_vec3<T>(
                two * dot(r3, v3) * r3 + (w * w - dot(r3,v3)) * v3 + two * w * cross(r3, v3)
            );
        }
    };

    GM_Q_OPERATOR_NUM_RIGHT(+)
    GM_Q_OPERATOR_NUM_RIGHT(-)
    GM_Q_OPERATOR_NUM_RIGHT(*)

    template<typename T>
    gm_quaternion<T> operator / (const T &value, const gm_quaternion<T> &v){
        GM_ASSERT(v.x != static_cast<T>(0) && v.y != static_cast<T>(0) && v.z != static_cast<T>(0) && v.w != static_cast<T>(0));
        return gm_quaternion<T>(static_cast<T>(value) / v.x, static_cast<T>(value) / v.y, static_cast<T>(value) / v.z, static_cast<T>(value) / v.w);
    }

    template<typename T>
    gm_vec3<T> operator * (const gm_vec3<T> &v3, const gm_quaternion<T> &q) {
        gm_vec3<T> r3(q.x, q.y, q.z);
        T two = static_cast<T>(2);
        return gm_vec3<T>(
            two * dot(r3, v3) * r3 + (q.w * q.w - dot(r3,v3)) * v3 + two * q.w * cross(r3, v3)
        );
    }

    template<typename T>
    std::ostream& operator << (std::ostream &os, const gm_quaternion<T> &v){
        using namespace std;
        os << setprecision(GM_OUTPUT_PRECISION)
           << setw(GM_OUTPUT_WIDTH)
           << GM_OUTPUT_POINT
           <<"[(" << v.x << ", " << v.y << ", " << v.z << "), " << v.w << "] ";

        return os;
    }

    template<typename T>
    T length(const gm_quaternion<T> &v){
        return static_cast<T>(sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w));
    }

    template<typename T>
    gm_quaternion<T> normalize(const gm_quaternion<T> &v) {
        T avg = length(v);
        bool isNoZero = avg != static_cast<T>(0);
        GM_ASSERT(isNoZero);

        return isNoZero ? gm_quaternion<T>(v.x/avg, v.y/avg, v.z/avg, v.w/avg) : gm_quaternion<T>();
    }

    template<typename T>
    T dot(const gm_quaternion<T> &vL, const gm_quaternion<T> &vR) {
        return vL.x * vR.x + vL.y * vR.y + vL.z * vR.z + vL.w * vR.w;
    }

    template<typename T>
    gm_quaternion<T> conjugate(const gm_quaternion<T> &q) {
        return gm_quaternion<T>(-q.x, -q.y, -q.z, q.w);
    }

    template<typename T>
    T rotationAngle(const gm_quaternion<T> &q){
        return static_cast<T>(acosSafe(q.w) * 2.0f);
    }

    template<typename T>
    gm_vec3<T> rotationAxis(const gm_quaternion<T> &q){
        T sinThetaPow2 = 1.0f - q.w * q.w;
        bool isPositive =  sinThetaPow2 > static_cast<T>(0);
        GM_ASSERT(isPositive);

        if (isPositive){
            T sinTheta = sqrt(sinThetaPow2);
            return gm_vec3<T>(q.x / sinTheta, q.y / sinTheta, q.z / sinTheta);
        } else {
            return gm_vec3<T>(0);
        }
    }

    template<typename T>
    gm_vec3<T> eulerAngle(const gm_quaternion<T> &q) {
        T h;
        T p = asinSafe(-2.0f * (q.y * q.z + q.w * q.x));
        T r = static_cast<T>(0);

        T cosP = cos(p);
        if (cosP != static_cast<T>(0)) {
            h = atan2(q.x * q.z - q.w * q.y, 0.5f - q.x * q.x - q.y * q.y);
            r = atan2(q.x * q.y - q.w * q.z, 0.5f - q.x * q.x - q.z * q.z);
        } else {
            h = atan2(-q.x * q.z - q.w * q.y, 0.5f - q.y * q.y - q.z * q.z);
        }
        
        return gm_vec3<T>(h, p, r);
    }

    template<typename T>
    gm_quaternion<T> pow(const gm_quaternion<T> &q, float exponent) {
        // This will protect against divide by zero
        if (fabs(q.w) > 0.9999f) {
            return q;
        }

        float alpha = acos(q.w);
        float newAlpha = alpha * exponent;
        float mult = sin(newAlpha) / sin(alpha);
        
        return gm_quaternion<T>(
            q.x * mult,
            q.y * mult,
            q.z * mult,
            cos(newAlpha)
        );
    }

    template<typename T>
    gm_quaternion<T> lerp(const gm_quaternion<T> &q0, const gm_quaternion<T> &q1, const float t) {
        return gm_quaternion<T>(static_cast<T>(1.0f - t) * q0 + t * q1);
    }

    template<typename T>
    gm_quaternion<T> nlerp(const gm_quaternion<T> &q0, const gm_quaternion<T> &q1, const float &t) {
        return normalize(lerp(q0, q1, t));
    }

    template<typename T>
    gm_quaternion<T> slerp(gm_quaternion<T> q0, gm_quaternion<T> q1, const float &t) {
        
        if (t <= 0.0f) return q0;
        if (t >= 1.0f) return q1;

        // Keep the shortest arc
        float cosTheta = float(dot(q0, q1));
        
        // q0 and q1 must be unit quaternions
        GM_ASSERT(cosTheta < 1.1f);

        if (cosTheta < 0.0f) {
            q1 = -q1;
            cosTheta = -cosTheta;
        }

        float k0, k1;
        if (cosTheta > 0.9999f) {
            // Very close - just use linear interpolation,
            // which will protect againt a divide by zero
            k0 = 1.0f - t;
            k1 = t;
        } else {
            float sinTheta = sqrt(1.0f - cosTheta*cosTheta);
            float theta = atan2(sinTheta, cosTheta);
            float oneOverSinTheta = 1.0f / sinTheta;
            k0 = sin((1.0f - t) * theta) * oneOverSinTheta;
            k1 = sin(t * theta) * oneOverSinTheta;
        }

        return gm_quaternion<T>(static_cast<T>(k0) * q0 + static_cast<T>(k1) * q1);
    }

}

#endif //GM_QUATERNION_H
