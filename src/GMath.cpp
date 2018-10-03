#include <iostream>
#include <iomanip>
#include <math.h>


// PI / 180.0
#define ANGLE_TO_RADIAN 0.017453

#define FLOAT_OPERATOR_V3(symbol) \
template<typename T> \
sfl_vec3<T> operator symbol (const T &value, const sfl_vec3<T> &vector){\
    return sfl_vec3<T>(static_cast<T>(value) symbol vector.x, static_cast<T>(value) symbol vector.y, static_cast<T>(value) symbol vector.z);\
}
#define FLOAT_OPERATOR_V4(symbol) \
template<typename T> \
sfl_vec4<T> operator symbol (const T &value, const sfl_vec4<T> &vector){\
    return sfl_vec4<T>(static_cast<T>(value) symbol vector.x, static_cast<T>(value) symbol vector.y, static_cast<T>(value) symbol vector.z, static_cast<T>(value) symbol vector.w);\
}

#define FLOAT_OPERATOR_MAT(type, size, symbol)\
template<typename T> \
type operator symbol (const T &value, const type& m){\
    type mTmp;\
    for (int i = 0; i < size; ++i){\
        for (int j = 0; j < size; ++j){\
            mTmp[i][j] = static_cast<T>(value) symbol m[i][j];\
        }\
    }\
\
    return mTmp;\
}

#define VEC_DISTANCE(type) \
template<typename T> \
T distance(const type &vFrom, const type &vTo) { \
    T disX = vTo.x - vFrom.x;\
    T disY = vTo.y - vFrom.y;\
    T disZ = vTo.z - vFrom.z;\
\
    return static_cast<T>(sqrt(disX*disX +  disY*disY + disZ*disZ));\
}

namespace SFL {

    // -- value left multiply vector or matrix ---------------------
    FLOAT_OPERATOR_V3(+)
    FLOAT_OPERATOR_V3(-)
    FLOAT_OPERATOR_V3(*)
    FLOAT_OPERATOR_V3(/)

    FLOAT_OPERATOR_V4(+)
    FLOAT_OPERATOR_V4(-)
    FLOAT_OPERATOR_V4(*)
    FLOAT_OPERATOR_V4(/)

    FLOAT_OPERATOR_MAT(sfl_mat3<T>, 3, +)
    FLOAT_OPERATOR_MAT(sfl_mat3<T>, 3, -)
    FLOAT_OPERATOR_MAT(sfl_mat3<T>, 3, *)
    FLOAT_OPERATOR_MAT(sfl_mat3<T>, 3, /)

    FLOAT_OPERATOR_MAT(sfl_mat4<T>, 4, +)
    FLOAT_OPERATOR_MAT(sfl_mat4<T>, 4, -)
    FLOAT_OPERATOR_MAT(sfl_mat4<T>, 4, *)
    FLOAT_OPERATOR_MAT(sfl_mat4<T>, 4, /)

    // -- value left multiply vector or matrix ---------------------
    template<typename T>
    sfl_mat3<T> operator * (const sfl_vec3<T> &v3, const sfl_mat3<T> &m3) {
        T col0Sum = m3[0][0] + m3[0][1] + m3[0][2];
        T col1Sum = m3[1][0] + m3[1][1] + m3[1][2];
        T col2Sum = m3[2][0] + m3[2][1] + m3[2][2];

        sfl_vec3<T> col = sfl_vec3<T>(col0Sum, col1Sum, col2Sum);

        return sfl_mat3<T>(v3.x * col, v3.y * col, v3.z * col);
    }

    template<typename T>
    sfl_mat4<T> operator * (const sfl_vec4<T> &v4, const sfl_mat4<T> &m4) {
        T col0Sum = m4[0][0] + m4[0][1] + m4[0][2] + m4[0][3];
        T col1Sum = m4[1][0] + m4[1][1] + m4[1][2] + m4[1][3];
        T col2Sum = m4[2][0] + m4[2][1] + m4[2][2] + m4[2][3];
        T col3Sum = m4[3][0] + m4[3][1] + m4[3][2] + m4[3][3];

        sfl_vec4<T> col = sfl_vec4<T>(col0Sum, col1Sum, col2Sum, col3Sum);

        return sfl_mat4<T>(v4.x * col, v4.y * col, v4.z * col, v4.w * col);
    }

    // -- linear algebra ---------------------
    VEC_DISTANCE(sfl_vec3<T>)
    VEC_DISTANCE(sfl_vec4<T>)






}
