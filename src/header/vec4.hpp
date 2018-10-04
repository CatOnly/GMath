#ifndef GM_VEC4_H
#define GM_VEC4_H

#include "vec3.hpp"

#define V4_OPERATOR_BASE(symbol) \
gm_vec4<T> operator symbol (const gm_vec4<T> &a) const {\
    return gm_vec4<T>(x symbol a.x, y symbol a.y, z symbol a.z, w symbol a.w);\
}

#define V4_OPERATOR_SELF(symbol) \
gm_vec4<T>& operator symbol (const gm_vec4<T> &a){\
    x symbol a.x;\
    y symbol a.y;\
    z symbol a.z;\
    w symbol a.w;\
\
    return *this;\
}

#define V4_OPERATOR_SELF_LAST(symbol) \
gm_vec4<T> operator symbol (int){\
    gm_vec4<T> tmp(*this);\
    symbol x;\
    symbol y;\
    symbol z;\
    symbol w;\
\
    return tmp;\
}
#define V4_OPERATOR_SELF_FIRST(symbol) \
gm_vec4<T>& operator symbol (){\
    symbol x;\
    symbol y;\
    symbol z;\
    symbol w;\
\
    return *this;\
}

#define V4_OPERATOR_NUM_LEFT(symbol)\
gm_vec4<T> operator symbol (const T &value) const {\
    gm_vec4<T> v;\
    v.x = x symbol value;\
    v.y = y symbol value;\
    v.z = z symbol value;\
    v.w = w symbol value;\
\
    return v;\
}

#define V4_OPERATOR_SELF_NUM_LEFT(symbol)\
gm_vec4<T>& operator symbol (const T &value){\
    x symbol value;\
    y symbol value;\
    z symbol value;\
    w symbol value;\
\
    return *this;\
}

#define V4_OPERATOR_NUM_RIGHT(symbol)\
template<typename T> \
gm_vec4<T> operator symbol (const T &value, const gm_vec4<T> &v){\
    return gm_vec4<T>(static_cast<T>(value) symbol v.x, static_cast<T>(value) symbol v.y, static_cast<T>(value) symbol v.z, static_cast<T>(value) symbol v.w);\
}

namespace gm {

    template <typename T> class gm_vec4
    {
    public:
        union { T x, r, s; };
        union { T y, g, t; };
        union { T z, b, p; };
        union { T w, a, q; };

        gm_vec4(T x, T y, T z, T w):x(static_cast<T>(x)),y(static_cast<T>(y)),z(static_cast<T>(z)),w(static_cast<T>(w)){}
        gm_vec4(T x = static_cast<T>(0)):gm_vec4(x,x,x,x){}
        gm_vec4(const gm_vec4<T> &v):gm_vec4(v.x, v.y, v.z, v.w){}

        explicit gm_vec4(const gm_vec3<T> &v, const T w = static_cast<T>(0)):gm_vec4(v.x, v.y, v.z, w){}

        VEC_OPERATOR_INDEX(4)

        V4_OPERATOR_BASE(+)
        V4_OPERATOR_BASE(-)
        V4_OPERATOR_BASE(*)
        V4_OPERATOR_BASE(/)

        V4_OPERATOR_SELF(+=)
        V4_OPERATOR_SELF(-=)
        V4_OPERATOR_SELF(*=)
        V4_OPERATOR_SELF(/=)

        V4_OPERATOR_SELF_LAST(++)
        V4_OPERATOR_SELF_LAST(--)
        V4_OPERATOR_SELF_FIRST(++)
        V4_OPERATOR_SELF_FIRST(--)

        V4_OPERATOR_NUM_LEFT(+)
        V4_OPERATOR_NUM_LEFT(-)
        V4_OPERATOR_NUM_LEFT(*)
        V4_OPERATOR_NUM_LEFT(/)

        V4_OPERATOR_SELF_NUM_LEFT(+=)
        V4_OPERATOR_SELF_NUM_LEFT(-=)
        V4_OPERATOR_SELF_NUM_LEFT(*=)
        V4_OPERATOR_SELF_NUM_LEFT(/=)
    };

    V4_OPERATOR_NUM_RIGHT(+)
    V4_OPERATOR_NUM_RIGHT(-)
    V4_OPERATOR_NUM_RIGHT(*)
    V4_OPERATOR_NUM_RIGHT(/)
}

#endif // GM_VEC4_H
