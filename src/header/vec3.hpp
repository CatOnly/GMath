#ifndef SFL_VEC3_H
#define SFL_VEC3_H

#include <cassert>

#define V3_OPERATOR_BASE(symbol) \
SFLVec3 operator symbol (const SFLVec3 &a){\
    return SFLVec3(x symbol a.x, y symbol a.y, z symbol a.z);\
}

#define V3_OPERATOR_SELF(symbol) \
SFLVec3& operator symbol (const SFLVec3 &a){\
    x symbol a.x;\
    y symbol a.y;\
    z symbol a.z;\
\
    return *this;\
}

#define V3_OPERATOR_SELF_LAST(symbol) \
SFLVec3 operator symbol (int){\
    SFLVec3 tmp(*this);\
    symbol x;\
    symbol y;\
    symbol z;\
\
    return tmp;\
}
#define V3_OPERATOR_SELF_FIRST(symbol) \
SFLVec3& operator symbol (){\
    symbol x;\
    symbol y;\
    symbol z;\
\
    return *this;\
}

namespace SFL {

    template <typename T> class sfl_vec3
    {
    public:
        union { T x, r, s;};
        union { T y, g, t;};
        union { T z, b, p;};

        typedef sfl_vec3<T> SFLVec3;

        sfl_vec3(T x, T y, T z):x(static_cast<T>(x)),y(static_cast<T>(y)),z(static_cast<T>(z)){}
        sfl_vec3(T x = 0.0f):sfl_vec3(static_cast<T>(x), static_cast<T>(x), static_cast<T>(x)){}
        sfl_vec3(const sfl_vec3<T> &vec):sfl_vec3(vec.x, vec.y, vec.z){}

        T & operator[](int i) const {
            assert(i >= 0 && i < 3);
            return (&x)[i];
        }

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

#endif // SFL_VEC3_H
