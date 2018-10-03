#ifndef GM_VEC3_H
#define GM_VEC3_H

#include "vec2.hpp"

#define V3_OPERATOR_BASE(symbol) \
GMVec3 operator symbol (const GMVec3 &a){\
    return GMVec3(x symbol a.x, y symbol a.y, z symbol a.z);\
}

#define V3_OPERATOR_SELF(symbol) \
GMVec3& operator symbol (const GMVec3 &a){\
    x symbol a.x;\
    y symbol a.y;\
    z symbol a.z;\
\
    return *this;\
}

#define V3_OPERATOR_SELF_LAST(symbol) \
GMVec3 operator symbol (int){\
    GMVec3 tmp(*this);\
    symbol x;\
    symbol y;\
    symbol z;\
\
    return tmp;\
}
#define V3_OPERATOR_SELF_FIRST(symbol) \
GMVec3& operator symbol (){\
    symbol x;\
    symbol y;\
    symbol z;\
\
    return *this;\
}

#define FLOAT_OPERATOR_V3(symbol) \
template<typename T> \
sfl_vec3<T> operator symbol (const T &value, const sfl_vec3<T> &vector){\
    return sfl_vec3<T>(static_cast<T>(value) symbol vector.x, static_cast<T>(value) symbol vector.y, static_cast<T>(value) symbol vector.z);\
}

namespace gm {

    template <typename T> class gm_vec3
    {
    public:
        union { T x, r, s;};
        union { T y, g, t;};
        union { T z, b, p;};

        gm_vec3(T x, T y, T z):x(x),y(y),z(z){}
        gm_vec3(T x = static_cast<T>(0)):gm_vec3(x,x,x){}
        gm_vec3(const gm_vec3<T> &vec):gm_vec3(vec.x, vec.y, vec.z){}

        typedef gm_vec3<T> GMVec3;

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
    };
}

#endif // GM_VEC3_H
