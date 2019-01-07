#ifndef GM_VEC3_H
#define GM_VEC3_H

#include "vec2.hpp"

#define GM_V3_OPERATOR_BASE(symbol) \
gm_vec3<T> operator symbol (const gm_vec3<T> &v) const {\
    return gm_vec3<T>(x symbol v.x, y symbol v.y, z symbol v.z);\
}

#define GM_V3_OPERATOR_SELF(symbol) \
gm_vec3<T>& operator symbol (const gm_vec3<T> &v){\
    x symbol v.x;\
    y symbol v.y;\
    z symbol v.z;\
\
    return *this;\
}

#define GM_V3_OPERATOR_SELF_LAST(symbol) \
gm_vec3<T> operator symbol (int){\
    gm_vec3<T> tmp(*this);\
    symbol x;\
    symbol y;\
    symbol z;\
\
    return tmp;\
}
#define GM_V3_OPERATOR_SELF_FIRST(symbol) \
gm_vec3<T>& operator symbol (){\
    symbol x;\
    symbol y;\
    symbol z;\
\
    return *this;\
}

#define GM_V3_OPERATOR_NUM_RIGHT(symbol)\
gm_vec3<T> operator symbol (const T &value) const {\
    gm_vec3<T> v;\
    v.x = x symbol value;\
    v.y = y symbol value;\
    v.z = z symbol value;\
\
    return v;\
}

#define GM_V3_OPERATOR_SELF_NUM_RIGHT(symbol)\
gm_vec3<T>& operator symbol (const T &value){\
    x symbol value;\
    y symbol value;\
    z symbol value;\
\
    return *this;\
}

#define GM_V3_OPERATOR_NUM_LEFT(symbol)\
template<typename T> \
gm_vec3<T> operator symbol (const T &value, const gm_vec3<T> &v){\
    return gm_vec3<T>(value symbol v.x, value symbol v.y, value symbol v.z);\
}

namespace gm {

    template <typename T> class gm_vec3
    {
    public:
        union { T x, r, s;};
        union { T y, g, t;};
        union { T z, b, p;};

        gm_vec3(const T x, const T y, const T z):x(static_cast<T>(x)),y(static_cast<T>(y)),z(static_cast<T>(z)){}
        gm_vec3(const gm_vec3<T> &vec):gm_vec3(vec.x, vec.y, vec.z){}

        explicit gm_vec3(const T x = static_cast<T>(0)):gm_vec3(x,x,x){}
        explicit gm_vec3(const gm_vec2<T> &v, const T z = static_cast<T>(0)):gm_vec3(v.x,v.y,z){}

        gm_vec3<T> operator - () const {
            return gm_vec3<T>(
                x == static_cast<T>(0) ? x : -x, 
                y == static_cast<T>(0) ? y : -y,
                z == static_cast<T>(0) ? z : -z
            );
        }   

        GM_VEC_OPERATOR_INDEX(3)

        GM_V3_OPERATOR_BASE(+)
        GM_V3_OPERATOR_BASE(-)
        GM_V3_OPERATOR_BASE(*)

        GM_V3_OPERATOR_SELF(+=)
        GM_V3_OPERATOR_SELF(-=)
        GM_V3_OPERATOR_SELF(*=)

        GM_V3_OPERATOR_SELF_LAST(++)
        GM_V3_OPERATOR_SELF_LAST(--)
        GM_V3_OPERATOR_SELF_FIRST(++)
        GM_V3_OPERATOR_SELF_FIRST(--)

        GM_V3_OPERATOR_NUM_RIGHT(+)
        GM_V3_OPERATOR_NUM_RIGHT(-)
        GM_V3_OPERATOR_NUM_RIGHT(*)

        GM_V3_OPERATOR_SELF_NUM_RIGHT(+=)
        GM_V3_OPERATOR_SELF_NUM_RIGHT(-=)
        GM_V3_OPERATOR_SELF_NUM_RIGHT(*=)

        gm_vec3<T> operator / (const gm_vec3<T> &v) const {
            GM_ASSERT(v.x != static_cast<T>(0) && v.y != static_cast<T>(0) && v.z != static_cast<T>(0));
            return gm_vec3<T>(x / v.x, y / v.y, z / v.z);
        }

        gm_vec3<T>& operator /= (const gm_vec3<T> &v){
            GM_ASSERT(v.x != static_cast<T>(0) && v.y != static_cast<T>(0) && v.z != static_cast<T>(0));
            x /= v.x;
            y /= v.y;
            z /= v.z;

            return *this;
        }

        gm_vec3<T> operator / (const T &value) const {
            GM_ASSERT(value != static_cast<T>(0));
            gm_vec3<T> v;
            v.x = x / value;
            v.y = y / value;
            v.z = z / value;

            return v;
        }

        gm_vec3<T>& operator /= (const T &value){
            GM_ASSERT(value != static_cast<T>(0));
            x /= value;
            y /= value;
            z /= value;

            return *this;
        }

        bool isValueEqual(const gm_vec3<T>& v){
            return (v.x == x && v.y == y && v.z == z);
        }
    };

    GM_V3_OPERATOR_NUM_LEFT(+)
    GM_V3_OPERATOR_NUM_LEFT(-)
    GM_V3_OPERATOR_NUM_LEFT(*)

    template<typename T>
    gm_vec3<T> operator / (const T &value, const gm_vec3<T> &v){
        GM_ASSERT(v.x != static_cast<T>(0) && v.y != static_cast<T>(0) && v.z != static_cast<T>(0));
        return gm_vec3<T>(value / v.x, value / v.y, value / v.z);
    }

    template<typename T>
    std::ostream& operator << (std::ostream &os, const gm_vec3<T> &v){
        using namespace std;
        os << setprecision(GM_OUTPUT_PRECISION)
           << setw(GM_OUTPUT_WIDTH)
           << GM_OUTPUT_POINT
           <<"(" << v.x << ", " << v.y << ", " << v.z << ") ";

        return os;
    }

    template<typename T>
    T dot(const gm_vec3<T> &vL, const gm_vec3<T> &vR) {
        return vL.x * vR.x + vL.y * vR.y + vL.z * vR.z;
    }

    template<typename T>
    gm_vec3<T> cross(const gm_vec3<T> &vL, const gm_vec3<T> &vR) {
        return gm_vec3<T>(
            vL.y * vR.z - vL.z * vR.y,
            vL.z * vR.x - vL.x * vR.z,
            vL.x * vR.y - vL.y * vR.x
        );
    }

    template<typename T>
    T length(const gm_vec3<T> &v){
        return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    }

    template<typename T>
    T distance(const gm_vec3<T> &vFrom, const gm_vec3<T> &vTo) {
        T disX = vTo.x - vFrom.x;
        T disY = vTo.y - vFrom.y;
        T disZ = vTo.z - vFrom.z;

        return static_cast<T>(sqrt(disX*disX +  disY*disY + disZ*disZ));\
    }

    template<typename T>
    gm_vec3<T> normalize(const gm_vec3<T> &v) {
        T avg = length(v);
        bool isNoZero = avg != static_cast<T>(0);
        GM_ASSERT(isNoZero);

        return isNoZero ? gm_vec3<T>(v.x/avg, v.y/avg, v.z/avg) : gm_vec3<T>();
    }
}

#endif // GM_VEC3_H
