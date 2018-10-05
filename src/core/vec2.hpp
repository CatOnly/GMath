#ifndef GM_VEC2_H
#define GM_VEC2_H

#include <cassert>
#include <math.h>
#include <iostream>
#include <iomanip>

#include "config.h"

#define GM_VEC_OPERATOR_INDEX(size)\
T & operator[](int i) { \
    assert(i >= 0 && i < size);\
    return (&x)[i];\
}\
T const & operator[](int i) const { \
    assert(i >= 0 && i < size);\
    return (&x)[i];\
}

#define GM_V2_OPERATOR_BASE(symbol) \
gm_vec2<T> operator symbol (const gm_vec2<T> &v) const {\
    return gm_vec2<T>(x symbol v.x, y symbol v.y);\
}

#define GM_V2_OPERATOR_SELF(symbol) \
gm_vec2<T>& operator symbol (const gm_vec2<T> &v){\
    x symbol v.x;\
    y symbol v.y;\
\
    return *this;\
}

#define GM_V2_OPERATOR_SELF_LAST(symbol) \
gm_vec2<T> operator symbol (int){\
    gm_vec2<T> tmp(*this);\
    symbol x;\
    symbol y;\
\
    return tmp;\
}
#define GM_V2_OPERATOR_SELF_FIRST(symbol) \
gm_vec2<T>& operator symbol (){\
    symbol x;\
    symbol y;\
\
    return *this;\
}

#define GM_V2_OPERATOR_NUM_RIGHT(symbol)\
gm_vec2<T> operator symbol (const T &value) const {\
    gm_vec2<T> v;\
    v.x = x symbol value;\
    v.y = y symbol value;\
\
    return v;\
}

#define GM_V2_OPERATOR_SELF_NUM_RIGHT(symbol)\
gm_vec2<T>& operator symbol (const T &value){\
    x symbol value;\
    y symbol value;\
\
    return *this;\
}

#define GM_V2_OPERATOR_NUM_LEFT(symbol)\
template<typename T> \
gm_vec2<T> operator symbol (const T &value, const gm_vec2<T> &v){\
    return gm_vec2<T>(value symbol v.x, value symbol v.y);\
}

namespace gm {
    template <typename T> class gm_vec2
    {
    public:
        union { T x, r, s;};
        union { T y, g, t;};

        gm_vec2(T x, T y):x(static_cast<T>(x)),y(static_cast<T>(y)){}
        gm_vec2(T x = static_cast<T>(0)):gm_vec2(x,x){}
        gm_vec2(const gm_vec2<T> &vec):gm_vec2(vec.x, vec.y){}

        gm_vec2<T> operator - () const {
            return gm_vec2<T>(
                x == static_cast<T>(0) ? x : -x,
                y == static_cast<T>(0) ? y : -y
            );
        }

        GM_VEC_OPERATOR_INDEX(2)

        GM_V2_OPERATOR_BASE(+)
        GM_V2_OPERATOR_BASE(-)
        GM_V2_OPERATOR_BASE(*)
        GM_V2_OPERATOR_BASE(/)

        GM_V2_OPERATOR_SELF(+=)
        GM_V2_OPERATOR_SELF(-=)
        GM_V2_OPERATOR_SELF(*=)
        GM_V2_OPERATOR_SELF(/=)

        GM_V2_OPERATOR_SELF_LAST(++)
        GM_V2_OPERATOR_SELF_LAST(--)
        GM_V2_OPERATOR_SELF_FIRST(++)
        GM_V2_OPERATOR_SELF_FIRST(--)

        GM_V2_OPERATOR_NUM_RIGHT(+)
        GM_V2_OPERATOR_NUM_RIGHT(-)
        GM_V2_OPERATOR_NUM_RIGHT(*)
        GM_V2_OPERATOR_NUM_RIGHT(/)

        GM_V2_OPERATOR_SELF_NUM_RIGHT(+=)
        GM_V2_OPERATOR_SELF_NUM_RIGHT(-=)
        GM_V2_OPERATOR_SELF_NUM_RIGHT(*=)
        GM_V2_OPERATOR_SELF_NUM_RIGHT(/=)
    };

    GM_V2_OPERATOR_NUM_LEFT(+)
    GM_V2_OPERATOR_NUM_LEFT(-)
    GM_V2_OPERATOR_NUM_LEFT(*)
    GM_V2_OPERATOR_NUM_LEFT(/)

    template<typename T>
    std::ostream& operator << (std::ostream &os, const gm_vec2<T> &v){
        using namespace std;
        os << setprecision(GM_OUTPUT_PRECISION)
           << setw(GM_OUTPUT_WIDTH)
           << GM_OUTPUT_POINT
           <<"(" << v.x << ", " << v.y << ") ";

        return os;
    }

    template<typename T>
    T length(const gm_vec2<T> &v){
        return sqrt(v.x * v.x + v.y * v.y);
    }

    template<typename T>
    T distance(const gm_vec2<T> &vFrom, const gm_vec2<T> &vTo) {
        T disX = vTo.x - vFrom.x;
        T disY = vTo.y - vFrom.y;

        return static_cast<T>(sqrt(disX*disX +  disY*disY));\
    }

    template<typename T>
    gm_vec2<T> normalize(const gm_vec2<T> &v) {
        T avg = length(v);
        return gm_vec2<T>(v.x/avg, v.y/avg);
    }

    template<typename T>
    T dot(const gm_vec2<T> &vL, const gm_vec2<T> &vR) {
        return vL.x * vR.x + vL.y * vR.y;
    }
}

#endif // GM_VEC2_H
