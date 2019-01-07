#ifndef GM_VEC4_H
#define GM_VEC4_H

#include "vec3.hpp"

#define GM_V4_OPERATOR_BASE(symbol) \
gm_vec4<T> operator symbol (const gm_vec4<T> &a) const {\
    return gm_vec4<T>(x symbol a.x, y symbol a.y, z symbol a.z, w symbol a.w);\
}

#define GM_V4_OPERATOR_SELF(symbol) \
gm_vec4<T>& operator symbol (const gm_vec4<T> &a){\
    x symbol a.x;\
    y symbol a.y;\
    z symbol a.z;\
    w symbol a.w;\
\
    return *this;\
}

#define GM_V4_OPERATOR_SELF_LAST(symbol) \
gm_vec4<T> operator symbol (int){\
    gm_vec4<T> tmp(*this);\
    symbol x;\
    symbol y;\
    symbol z;\
    symbol w;\
\
    return tmp;\
}
#define GM_V4_OPERATOR_SELF_FIRST(symbol) \
gm_vec4<T>& operator symbol (){\
    symbol x;\
    symbol y;\
    symbol z;\
    symbol w;\
\
    return *this;\
}

#define GM_V4_OPERATOR_NUM_RIGHT(symbol)\
gm_vec4<T> operator symbol (const T &value) const {\
    gm_vec4<T> v;\
    v.x = x symbol value;\
    v.y = y symbol value;\
    v.z = z symbol value;\
    v.w = w symbol value;\
\
    return v;\
}

#define GM_V4_OPERATOR_SELF_NUM_RIGHT(symbol)\
gm_vec4<T>& operator symbol (const T &value){\
    x symbol value;\
    y symbol value;\
    z symbol value;\
    w symbol value;\
\
    return *this;\
}

#define GM_V4_OPERATOR_NUM_LEFT(symbol)\
template<typename T> \
gm_vec4<T> operator symbol (const T &value, const gm_vec4<T> &v){\
    return gm_vec4<T>(value symbol v.x, value symbol v.y, value symbol v.z, value symbol v.w);\
}

namespace gm {

    template <typename T> class gm_vec4
    {
    public:
        union { T x, r, s; };
        union { T y, g, t; };
        union { T z, b, p; };
        union { T w, a, q; };

        gm_vec4(const T x, const T y, const T z, const T w):x(static_cast<T>(x)),y(static_cast<T>(y)),z(static_cast<T>(z)),w(static_cast<T>(w)){}
        gm_vec4(const gm_vec4<T> &v):gm_vec4(v.x, v.y, v.z, v.w){}

        explicit gm_vec4(const T x = static_cast<T>(0)):gm_vec4(x,x,x,x){}
        explicit gm_vec4(const gm_vec3<T> &v, const T w = static_cast<T>(0)):gm_vec4(v.x, v.y, v.z, w){}

        gm_vec4<T> operator - () const {            
            return gm_vec4<T>(
                x == static_cast<T>(0) ? x : -x, 
                y == static_cast<T>(0) ? y : -y,
                z == static_cast<T>(0) ? z : -z,
                w == static_cast<T>(0) ? w : -w
            );
        }

        GM_VEC_OPERATOR_INDEX(4)

        GM_V4_OPERATOR_BASE(+)
        GM_V4_OPERATOR_BASE(-)
        GM_V4_OPERATOR_BASE(*)

        GM_V4_OPERATOR_SELF(+=)
        GM_V4_OPERATOR_SELF(-=)
        GM_V4_OPERATOR_SELF(*=)

        GM_V4_OPERATOR_SELF_LAST(++)
        GM_V4_OPERATOR_SELF_LAST(--)
        GM_V4_OPERATOR_SELF_FIRST(++)
        GM_V4_OPERATOR_SELF_FIRST(--)

        GM_V4_OPERATOR_NUM_RIGHT(+)
        GM_V4_OPERATOR_NUM_RIGHT(-)
        GM_V4_OPERATOR_NUM_RIGHT(*)

        GM_V4_OPERATOR_SELF_NUM_RIGHT(+=)
        GM_V4_OPERATOR_SELF_NUM_RIGHT(-=)
        GM_V4_OPERATOR_SELF_NUM_RIGHT(*=)

        gm_vec4<T> operator / (const gm_vec4<T> &v) const {
            GM_ASSERT(v.x != static_cast<T>(0) && v.y != static_cast<T>(0) && v.z != static_cast<T>(0) && v.w != static_cast<T>(0));
            return gm_vec4<T>(x / v.x, y / v.y, z / v.z, w / v.w);
        }

        gm_vec4<T>& operator /= (const gm_vec4<T> &v){
            GM_ASSERT(v.x != static_cast<T>(0) && v.y != static_cast<T>(0) && v.z != static_cast<T>(0) && v.w != static_cast<T>(0));
            x /= v.x;
            y /= v.y;
            z /= v.z;
            w /= v.w;

            return *this;
        }

        gm_vec4<T> operator / (const T &value) const {
            GM_ASSERT(value != static_cast<T>(0));
            gm_vec4<T> v;
            v.x = x / value;
            v.y = y / value;
            v.z = z / value;
            v.w = w / value;

            return v;
        }

        gm_vec4<T>& operator /= (const T &value){
            GM_ASSERT(value != static_cast<T>(0));
            x /= value;
            y /= value;
            z /= value;
            w /= value;

            return *this;
        }

        bool isValueEqual(const gm_vec4<T>& v){
            return (v.x == x && v.y == y && v.z == z && v.w == w);
        }
    };

    GM_V4_OPERATOR_NUM_LEFT(+)
    GM_V4_OPERATOR_NUM_LEFT(-)
    GM_V4_OPERATOR_NUM_LEFT(*)

    template<typename T>
    gm_vec4<T> operator / (const T &value, const gm_vec4<T> &v){
        GM_ASSERT(v.x != static_cast<T>(0) && v.y != static_cast<T>(0) && v.z != static_cast<T>(0) && v.w != static_cast<T>(0));
        return gm_vec4<T>(value / v.x, value / v.y, value / v.z, value / v.w);
    }

    template<typename T>
    std::ostream& operator << (std::ostream &os, const gm_vec4<T> &v){
        using namespace std;
        os << setprecision(GM_OUTPUT_PRECISION)
           << setw(GM_OUTPUT_WIDTH)
           << GM_OUTPUT_POINT
           <<"(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ") ";

        return os;
    }

    template<typename T>
    T dot(const gm_vec4<T> &vL, const gm_vec4<T> &vR) {
        return vL.x * vR.x + vL.y * vR.y + vL.z * vR.z + vL.w * vR.w;
    }

    template<typename T>
    T length(const gm_vec4<T> &v){
        return sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
    }

    template<typename T>
    T distance(const gm_vec4<T> &vFrom, const gm_vec4<T> &vTo) {
        T disX = vTo.x - vFrom.x;
        T disY = vTo.y - vFrom.y;
        T disZ = vTo.z - vFrom.z;
        T disW = vTo.w - vFrom.w;

        return static_cast<T>(sqrt(disX*disX +  disY*disY + disZ*disZ + disW*disW));\
    }

    template<typename T>
    gm_vec4<T> normalize(const gm_vec4<T> &v) {
        T avg = length(v);
        bool isNoZero = avg != static_cast<T>(0);
        GM_ASSERT(isNoZero);

        return isNoZero ? gm_vec4<T>(v.x/avg, v.y/avg, v.z/avg, v.w/avg) : gm_vec4<T>();
    }
}

#endif // GM_VEC4_H
