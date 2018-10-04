#ifndef GM_VEC3_H
#define GM_VEC3_H

#include "vec2.hpp"

#define V3_OPERATOR_BASE(symbol) \
gm_vec3<T> operator symbol (const gm_vec3<T> &v) const {\
    return gm_vec3<T>(x symbol v.x, y symbol v.y, z symbol v.z);\
}

#define V3_OPERATOR_SELF(symbol) \
gm_vec3<T>& operator symbol (const gm_vec3<T> &v){\
    x symbol v.x;\
    y symbol v.y;\
    z symbol v.z;\
\
    return *this;\
}

#define V3_OPERATOR_SELF_LAST(symbol) \
gm_vec3<T> operator symbol (int){\
    gm_vec3<T> tmp(*this);\
    symbol x;\
    symbol y;\
    symbol z;\
\
    return tmp;\
}
#define V3_OPERATOR_SELF_FIRST(symbol) \
gm_vec3<T>& operator symbol (){\
    symbol x;\
    symbol y;\
    symbol z;\
\
    return *this;\
}

#define V3_OPERATOR_NUM_LEFT(symbol)\
gm_vec3<T> operator symbol (const T &value) const {\
    gm_vec3<T> v;\
    v.x = x symbol value;\
    v.y = y symbol value;\
    v.z = z symbol value;\
\
    return v;\
}

#define V3_OPERATOR_SELF_NUM_LEFT(symbol)\
gm_vec3<T>& operator symbol (const T &value){\
    x symbol value;\
    y symbol value;\
    z symbol value;\
\
    return *this;\
}

#define V3_OPERATOR_NUM_RIGHT(symbol)\
template<typename T> \
gm_vec3<T> operator symbol (const T &value, const gm_vec3<T> &v){\
    return gm_vec3<T>(static_cast<T>(value) symbol v.x, static_cast<T>(value) symbol v.y, static_cast<T>(value) symbol v.z);\
}

namespace gm {

    template <typename T> class gm_vec3
    {
    public:
        union { T x, r, s;};
        union { T y, g, t;};
        union { T z, b, p;};

        gm_vec3(T x, T y, T z):x(static_cast<T>(x)),y(static_cast<T>(y)),z(static_cast<T>(z)){}
        gm_vec3(T x = static_cast<T>(0)):gm_vec3(x,x,x){}
        gm_vec3(const gm_vec3<T> &vec):gm_vec3(vec.x, vec.y, vec.z){}

        VEC_OPERATOR_INDEX(3)

        V3_OPERATOR_BASE(+)
        V3_OPERATOR_BASE(-)
        V3_OPERATOR_BASE(*)
        V3_OPERATOR_BASE(/)

        V3_OPERATOR_SELF(+=)
        V3_OPERATOR_SELF(-=)
        V3_OPERATOR_SELF(*=)
        V3_OPERATOR_SELF(/=)

        V3_OPERATOR_SELF_LAST(++)
        V3_OPERATOR_SELF_LAST(--)
        V3_OPERATOR_SELF_FIRST(++)
        V3_OPERATOR_SELF_FIRST(--)

        V3_OPERATOR_NUM_LEFT(+)
        V3_OPERATOR_NUM_LEFT(-)
        V3_OPERATOR_NUM_LEFT(*)
        V3_OPERATOR_NUM_LEFT(/)

        V3_OPERATOR_SELF_NUM_LEFT(+=)
        V3_OPERATOR_SELF_NUM_LEFT(-=)
        V3_OPERATOR_SELF_NUM_LEFT(*=)
        V3_OPERATOR_SELF_NUM_LEFT(/=)
    };

    V3_OPERATOR_NUM_RIGHT(+)
    V3_OPERATOR_NUM_RIGHT(-)
    V3_OPERATOR_NUM_RIGHT(*)
    V3_OPERATOR_NUM_RIGHT(/)
}

#endif // GM_VEC3_H
