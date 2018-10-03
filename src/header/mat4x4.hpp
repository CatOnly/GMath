#ifndef GM_MAT4X4_H
#define GM_MAT4X4_H

#include "vec4.hpp"
#include "mat.hpp"

namespace gm {

    template<typename T> class gm_mat4
    {
        gm_vec4<T> _column[4];

    public:
        gm_mat4(const gm_vec4<T> &col1, const gm_vec4<T> &col2, const gm_vec4<T> &col3, const gm_vec4<T> &col4){
            _column[0] = col1;
            _column[1] = col2;
            _column[2] = col3;
            _column[3] = col4;
        }

        gm_mat4(const gm_mat4<T> &m4) {
            _column[0] = m4[0];
            _column[1] = m4[1];
            _column[2] = m4[2];
            _column[3] = m4[3];
        }

        gm_mat4(const T x1, const T x2, const T x3, const T x4,
                const T y1, const T y2, const T y3, const T y4,
                const T z1, const T z2, const T z3, const T z4,
                const T w1, const T w2, const T w3, const T w4){
            _column[0] = gm_vec4<T>(x1, x2, x3, x4);
            _column[1] = gm_vec4<T>(y1, y2, y3, y4);
            _column[2] = gm_vec4<T>(z1, z2, z3, z4);
            _column[3] = gm_vec4<T>(w1, w2, w3, w4);
        }

        gm_mat4(const T x, const T y, const T z, const T w):gm_mat4(
                                                                 static_cast<T>(x), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0),
                                                                 static_cast<T>(0), static_cast<T>(y), static_cast<T>(0), static_cast<T>(0),
                                                                 static_cast<T>(0), static_cast<T>(0), static_cast<T>(y), static_cast<T>(0),
                                                                 static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(w)){}
        explicit gm_mat4(const gm_vec4<T> &vector4):gm_mat4(vector4.x, vector4.y, vector4.z, vector4.w){}
        explicit gm_mat4(const T value = static_cast<T>(1)):gm_mat4(value, value, value, value){}

        MAT_OPERATOR_INDEX(4)

        MAT_OPERATOR_BASE(4, +)
        MAT_OPERATOR_BASE(4, -)

        MAT_OPERATOR_SELF(4, +=)
        MAT_OPERATOR_SELF(4, -=)

        MAT_OPERATOR_NUM_LEFT(4, +)
        MAT_OPERATOR_NUM_LEFT(4, -)
        MAT_OPERATOR_NUM_LEFT(4, *)
        MAT_OPERATOR_NUM_LEFT(4, /)

        MAT_OPERATOR_SELF_NUM_LEFT(4, +=)
        MAT_OPERATOR_SELF_NUM_LEFT(4, -=)
        MAT_OPERATOR_SELF_NUM_LEFT(4, *=)
        MAT_OPERATOR_SELF_NUM_LEFT(4, /=)
    };

    MAT_OPERATOR_NUM_RIGHT(4, +)
    MAT_OPERATOR_NUM_RIGHT(4, -)
    MAT_OPERATOR_NUM_RIGHT(4, *)
    MAT_OPERATOR_NUM_RIGHT(4, /)
}

#endif // GM_MAT4X4_H
