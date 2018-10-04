#ifndef GM_QUATERNION_H
#define GM_QUATERNION_H

#include "vec4.hpp"

#define Q_OPERATOR_BASE(symbol) \
gm_quaternion<T> operator symbol (const gm_quaternion<T> &a){\
    return gm_quaternion<T>(x symbol a.x, y symbol a.y, z symbol a.z, w symbol a.w);\
}

#define Q_OPERATOR_NUM_LEFT(symbol)\
gm_quaternion<T> operator symbol (const T &value){\
    gm_quaternion<T> v;\
    v.x = x symbol value;\
    v.y = y symbol value;\
    v.z = z symbol value;\
    v.w = w symbol value;\
\
    return v;\
}

#define Q_OPERATOR_SELF_NUM_LEFT(symbol)\
gm_quaternion<T>& operator symbol (const T &value){\
    x symbol value;\
    y symbol value;\
    z symbol value;\
    w symbol value;\
\
    return *this;\
}

#define Q_OPERATOR_NUM_RIGHT(symbol)\
template<typename T> \
gm_quaternion<T> operator symbol (const T &value, const gm_quaternion<T> &v){\
    return gm_quaternion<T>(static_cast<T>(value) symbol v.x, static_cast<T>(value) symbol v.y, static_cast<T>(value) symbol v.z, static_cast<T>(value) symbol v.w);\
}

namespace gm {
    template <typename T> class gm_quaternion
    {
    public:
        T x, y, z, w;

        gm_quaternion(T x = static_cast<T>(0), T y = static_cast<T>(0), T z = static_cast<T>(0), T w = static_cast<T>(1)):x(static_cast<T>(x)),y(static_cast<T>(y)),z(static_cast<T>(z)),w(static_cast<T>(w)){}
        gm_quaternion(const gm_quaternion<T> &v):gm_quaternion(v.x, v.y, v.z, v.w){}

        explicit gm_quaternion(const gm_vec3<T> &v, const T w = static_cast<T>(1)):gm_quaternion(v.x, v.y, v.z, w){}

        gm_quaternion<T> operator * (const gm_quaternion<T> &q){
            return gm_quaternion<T>();
        }

        VEC_OPERATOR_INDEX(4)

        Q_OPERATOR_BASE(+)
        Q_OPERATOR_BASE(-)

        Q_OPERATOR_NUM_LEFT(+)
        Q_OPERATOR_NUM_LEFT(-)
        Q_OPERATOR_NUM_LEFT(*)
        Q_OPERATOR_NUM_LEFT(/)

        Q_OPERATOR_SELF_NUM_LEFT(+=)
        Q_OPERATOR_SELF_NUM_LEFT(-=)
        Q_OPERATOR_SELF_NUM_LEFT(*=)
        Q_OPERATOR_SELF_NUM_LEFT(/=)
    };

    Q_OPERATOR_NUM_RIGHT(+)
    Q_OPERATOR_NUM_RIGHT(-)
    Q_OPERATOR_NUM_RIGHT(*)
    Q_OPERATOR_NUM_RIGHT(/)
}

#endif //GM_QUATERNION_H