#ifndef SFL_VEC4_H
#define SFL_VEC4_H

#include "vec3.hpp"

#define V4_OPERATOR_BASE(symbol) \
SFLVec4 operator symbol (const SFLVec4 &a){\
    return SFLVec4(x symbol a.x, y symbol a.y, z symbol a.z, w symbol a.w);\
}

#define V4_OPERATOR_SELF(symbol) \
SFLVec4& operator symbol (const SFLVec4 &a){\
    x symbol a.x;\
    y symbol a.y;\
    z symbol a.z;\
    w symbol a.w;\
\
    return *this;\
}

#define V4_OPERATOR_SELF_LAST(symbol) \
SFLVec4 operator symbol (int){\
    SFLVec4 tmp(*this);\
    symbol x;\
    symbol y;\
    symbol z;\
    symbol w;\
\
    return tmp;\
}
#define V4_OPERATOR_SELF_FIRST(symbol) \
SFLVec4& operator symbol (){\
    symbol x;\
    symbol y;\
    symbol z;\
    symbol w;\
\
    return *this;\
}

namespace SFL {

    template <typename T> class sfl_vec4
    {
    public:
        union { T x, r, s; };
        union { T y, g, t; };
        union { T z, b, p; };
        union { T w, a, q; };

        typedef sfl_vec4<T> SFLVec4;

        sfl_vec4(T x, T y, T z, T w):x(static_cast<T>(x)),y(static_cast<T>(y)),z(static_cast<T>(z)),w(static_cast<T>(w)){}
        sfl_vec4(T x = 0.0f):sfl_vec4(static_cast<T>(x),static_cast<T>(x),static_cast<T>(x),static_cast<T>(x)){}
        sfl_vec4(const sfl_vec4<T> &vec):sfl_vec4(vec.x, vec.y, vec.z, vec.w){}

        explicit sfl_vec4(const sfl_vec3<T> &vec):sfl_vec4(vec.x, vec.y, vec.z, 0.0f){}

        T & operator[](int i) const {
            assert(i >= 0 && i < 4);
            return (&x)[i];
        }

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

#endif // SFL_VEC4_H
