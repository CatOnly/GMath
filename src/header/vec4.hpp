#ifndef GM_VEC4_H
#define GM_VEC4_H

#include "vec3.hpp"

#define V4_OPERATOR_BASE(symbol) \
GMVec4 operator symbol (const GMVec4 &a){\
    return GMVec4(x symbol a.x, y symbol a.y, z symbol a.z, w symbol a.w);\
}

#define V4_OPERATOR_SELF(symbol) \
GMVec4& operator symbol (const GMVec4 &a){\
    x symbol a.x;\
    y symbol a.y;\
    z symbol a.z;\
    w symbol a.w;\
\
    return *this;\
}

#define V4_OPERATOR_SELF_LAST(symbol) \
GMVec4 operator symbol (int){\
    GMVec4 tmp(*this);\
    symbol x;\
    symbol y;\
    symbol z;\
    symbol w;\
\
    return tmp;\
}
#define V4_OPERATOR_SELF_FIRST(symbol) \
GMVec4& operator symbol (){\
    symbol x;\
    symbol y;\
    symbol z;\
    symbol w;\
\
    return *this;\
}

namespace gm {

    template <typename T> class gm_vec4
    {
    public:
        union { T x, r, s; };
        union { T y, g, t; };
        union { T z, b, p; };
        union { T w, a, q; };

        gm_vec4(T x, T y, T z, T w):x(x),y(y),z(z),w(w){}
        gm_vec4(T x = static_cast<T>(0)):gm_vec4(x,x,x,x){}
        gm_vec4(const gm_vec4<T> &vec):gm_vec4(vec.x, vec.y, vec.z, vec.w){}

        explicit gm_vec4(const gm_vec3<T> &vec):gm_vec4(vec.x, vec.y, vec.z, 0.0f){}

        typedef gm_vec4<T> GMVec4;

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
    };
}

#endif // GM_VEC4_H
