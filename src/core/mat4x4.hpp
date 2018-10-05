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
                                                                 static_cast<T>(0), static_cast<T>(0), static_cast<T>(z), static_cast<T>(0),
                                                                 static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(w)){}
        explicit gm_mat4(const gm_vec4<T> &vector4):gm_mat4(vector4.x, vector4.y, vector4.z, vector4.w){}
        explicit gm_mat4(const T value = static_cast<T>(1)):gm_mat4(value, value, value, value){}

        GM_MAT_OPERATOR_INDEX(4)

        GM_MAT_OPERATOR_BASE(4, +)
        GM_MAT_OPERATOR_BASE(4, -)

        GM_MAT_OPERATOR_SELF(4, +=)
        GM_MAT_OPERATOR_SELF(4, -=)

        GM_MAT_OPERATOR_NUM_LEFT(4, +)
        GM_MAT_OPERATOR_NUM_LEFT(4, -)
        GM_MAT_OPERATOR_NUM_LEFT(4, *)
        GM_MAT_OPERATOR_NUM_LEFT(4, /)

        GM_MAT_OPERATOR_SELF_NUM_LEFT(4, +=)
        GM_MAT_OPERATOR_SELF_NUM_LEFT(4, -=)
        GM_MAT_OPERATOR_SELF_NUM_LEFT(4, *=)
        GM_MAT_OPERATOR_SELF_NUM_LEFT(4, /=)
    };

    GM_MAT_OPERATOR_NUM_RIGHT(4, +)
    GM_MAT_OPERATOR_NUM_RIGHT(4, -)
    GM_MAT_OPERATOR_NUM_RIGHT(4, *)
    GM_MAT_OPERATOR_NUM_RIGHT(4, /)

    GM_MAT_VALUE_PTR_FROM(4)

    template<typename T>
    std::ostream& operator << (std::ostream &os, const gm_mat4<T> &m){
        using namespace std;
        os << setprecision(GM_OUTPUT_PRECISION)
           << setw(GM_OUTPUT_WIDTH)
           << GM_OUTPUT_POINT;

        for (int i = 0; i < 3; ++i){
            os << m[0][i] << " "
               << m[1][i] << " "
               << m[2][i] << " "
               << m[3][i] << " "
               << endl;
        }
    }

    template<typename T>
    gm_mat4<T> transport(const gm_mat4<T> &m) {
        return gm_mat4<T>(
            row(m, 0), 
            row(m, 1), 
            row(m, 2),
            row(m, 3)
        );
    }

    template<typename T>
    gm_vec4<T> row(gm_mat4<T> mat, int index) {
        return gm_vec4<T>(mat[0][index], mat[1][index], mat[2][index], mat[3][index]);
    }

    // -- vector * matrix --------------
    template<typename T>
    gm_mat4<T> operator * (const gm_vec4<T> &v4, const gm_mat4<T> &m4) {
        T col0Sum = m4[0][0] + m4[0][1] + m4[0][2] + m4[0][3];
        T col1Sum = m4[1][0] + m4[1][1] + m4[1][2] + m4[1][3];
        T col2Sum = m4[2][0] + m4[2][1] + m4[2][2] + m4[2][3];
        T col3Sum = m4[3][0] + m4[3][1] + m4[3][2] + m4[3][3];

        gm_vec4<T> colSum = gm_vec4<T>(col0Sum, col1Sum, col2Sum, col3Sum);

        return gm_mat4<T>(v4.x * colSum, v4.y * colSum, v4.z * colSum, v4.w * colSum);
    }

    // -- matrix * vector --------------
    template<typename T>
    gm_vec4<T> operator * (const gm_mat4<T> &mat, const gm_vec4<T> &col) {
        return gm_vec4<T>(
            dot(row(mat, 0), col), 
            dot(row(mat, 1), col), 
            dot(row(mat, 2), col), 
            dot(row(mat, 3), col)
        );
    }

    // -- matrix * matrix --------------
    template<typename T>
    gm_mat4<T> operator * (const gm_mat4<T> &matL, const gm_mat4<T> &matR) {
        gm_vec4<T> row0 = row(matL, 0);
        gm_vec4<T> row1 = row(matL, 1);
        gm_vec4<T> row2 = row(matL, 2);
        gm_vec4<T> row3 = row(matL, 3);

        const gm_vec4<T> &col0 = matR[0];
        const gm_vec4<T> &col1 = matR[1];
        const gm_vec4<T> &col2 = matR[2];
        const gm_vec4<T> &col3 = matR[3];

        return gm_mat4<T>(
            dot(row0,col0), dot(row1,col0), dot(row2,col0), dot(row3,col0),
            dot(row0,col1), dot(row1,col1), dot(row2,col1), dot(row3,col1),
            dot(row0,col2), dot(row1,col2), dot(row2,col2), dot(row3,col2),
            dot(row0,col3), dot(row1,col3), dot(row2,col3), dot(row3,col3)
        );
    }
}

#endif // GM_MAT4X4_H
