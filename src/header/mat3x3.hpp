#ifndef GM_MAT3X3_H
#define GM_MAT3X3_H

#include "vec3.hpp"
#include "mat.hpp"

namespace gm {

    template<typename T> class gm_mat3
    {
        gm_vec3<T> _column[3];        

    public:
        gm_mat3(const gm_vec3<T> &col1, const gm_vec3<T> &col2, const gm_vec3<T> &col3){
            _column[0] = col1;
            _column[1] = col2;
            _column[2] = col3;
        }

        gm_mat3(const gm_mat3<T> &m3) {
            _column[0] = m3[0];
            _column[1] = m3[1];
            _column[2] = m3[2];
        }

        gm_mat3(const T x1, const T x2, const T x3,
                const T y1, const T y2, const T y3,
                const T z1, const T z2, const T z3){
            _column[0] = gm_vec3<T>(x1, x2, x3);
            _column[1] = gm_vec3<T>(y1, y2, y3);
            _column[2] = gm_vec3<T>(z1, z2, z3);
        }
        gm_mat3(const T x, const T y, const T z):gm_mat3(static_cast<T>(x), static_cast<T>(0), static_cast<T>(0),
                                                         static_cast<T>(0), static_cast<T>(y), static_cast<T>(0),
                                                         static_cast<T>(0), static_cast<T>(0), static_cast<T>(z)){}
        explicit gm_mat3(const gm_vec3<T> &vector3):gm_mat3(vector3.x, vector3.y, vector3.z){}
        explicit gm_mat3(const T value = static_cast<T>(1)):gm_mat3(value, value, value){}

        MAT_OPERATOR_INDEX(3)

        MAT_OPERATOR_BASE(3, +)
        MAT_OPERATOR_BASE(3, -)

        MAT_OPERATOR_SELF(3, +=)
        MAT_OPERATOR_SELF(3, -=)

        MAT_OPERATOR_NUM_LEFT(3, +)
        MAT_OPERATOR_NUM_LEFT(3, -)
        MAT_OPERATOR_NUM_LEFT(3, *)
        MAT_OPERATOR_NUM_LEFT(3, /)

        MAT_OPERATOR_SELF_NUM_LEFT(3, +=)
        MAT_OPERATOR_SELF_NUM_LEFT(3, -=)
        MAT_OPERATOR_SELF_NUM_LEFT(3, *=)
        MAT_OPERATOR_SELF_NUM_LEFT(3, /=)
    };

    MAT_OPERATOR_NUM_RIGHT(3, +)
    MAT_OPERATOR_NUM_RIGHT(3, -)
    MAT_OPERATOR_NUM_RIGHT(3, *)
    MAT_OPERATOR_NUM_RIGHT(3, /)
}

#endif // GM_MAT3X3_H
