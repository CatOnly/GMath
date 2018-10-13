#ifndef GM_MAT3X3_H
#define GM_MAT3X3_H

#include "vec3.hpp"
#include "mat2x2.hpp"

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

        explicit gm_mat3(const gm_mat2<T> &m2){
            _column[0] = gm_vec3<T>(m2[0]);
            _column[1] = gm_vec3<T>(m2[1]);
            _column[2] = gm_vec3<T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(1));
        }

        gm_mat3<T> operator - () const {
            return gm_mat3<T>(
                -_column[0],
                -_column[1],
                -_column[2]
            );
        }

        GM_MAT_OPERATOR_INDEX(3)

        GM_MAT_OPERATOR_BASE(3, +)
        GM_MAT_OPERATOR_BASE(3, -)

        GM_MAT_OPERATOR_SELF(3, +=)
        GM_MAT_OPERATOR_SELF(3, -=)

        GM_MAT_OPERATOR_NUM_LEFT(3, +)
        GM_MAT_OPERATOR_NUM_LEFT(3, -)
        GM_MAT_OPERATOR_NUM_LEFT(3, *)
        GM_MAT_OPERATOR_NUM_LEFT(3, /)

        GM_MAT_OPERATOR_SELF_NUM_LEFT(3, +=)
        GM_MAT_OPERATOR_SELF_NUM_LEFT(3, -=)
        GM_MAT_OPERATOR_SELF_NUM_LEFT(3, *=)
        GM_MAT_OPERATOR_SELF_NUM_LEFT(3, /=)
    };

    GM_MAT_OPERATOR_NUM_RIGHT(3, +)
    GM_MAT_OPERATOR_NUM_RIGHT(3, -)
    GM_MAT_OPERATOR_NUM_RIGHT(3, *)
    GM_MAT_OPERATOR_NUM_RIGHT(3, /)

    GM_MAT_VALUE_PTR_FROM(3)

    template<typename T>
    std::ostream& operator << (std::ostream &os, const gm_mat3<T> &m){
        using namespace std;
        os << setprecision(GM_OUTPUT_PRECISION)
           << setw(GM_OUTPUT_WIDTH)
           << GM_OUTPUT_POINT;

        for (int i = 0; i < 3; ++i){
            os << m[0][i] << " "
               << m[1][i] << " "
               << m[2][i];
            if (i != 2) os << endl;
        }

        return os;
    }

    template<typename T>
    gm_mat3<T> transport(const gm_mat3<T> &m) {
        return gm_mat3<T>(
            row(m, 0), 
            row(m, 1), 
            row(m, 2)
        );
    }

    template<typename T>
    gm_vec3<T> row(gm_mat3<T> mat, int index) {
        return gm_vec3<T>(mat[0][index], mat[1][index], mat[2][index]);
    }

    // -- vector * matrix --------------
    template<typename T>
    gm_mat3<T> operator * (const gm_vec3<T> &v3, const gm_mat3<T> &m3) {
        T col0Sum = m3[0][0] + m3[0][1] + m3[0][2];
        T col1Sum = m3[1][0] + m3[1][1] + m3[1][2];
        T col2Sum = m3[2][0] + m3[2][1] + m3[2][2];

        gm_vec3<T> colSum = gm_vec3<T>(col0Sum, col1Sum, col2Sum);

        return gm_mat3<T>(v3.x * colSum, v3.y * colSum, v3.z * colSum);
    }

    // -- matrix * vector --------------
    template<typename T>
    gm_vec3<T> operator * (const gm_mat3<T> &mat, const gm_vec3<T> &col) {
        return gm_vec3<T>(
            dot(row(mat, 0), col), 
            dot(row(mat, 1), col), 
            dot(row(mat, 2), col)
        );
    }

    // -- matrix * matrix --------------
    template<typename T>
    gm_mat3<T> operator * (const gm_mat3<T> &matL, const gm_mat3<T> &matR) {
        gm_vec3<T> row0 = row(matL, 0);
        gm_vec3<T> row1 = row(matL, 1);
        gm_vec3<T> row2 = row(matL, 2);

        const gm_vec3<T> &col0 = matR[0];
        const gm_vec3<T> &col1 = matR[1];
        const gm_vec3<T> &col2 = matR[2];

        return gm_mat3<T>(
            dot(row0, col0), dot(row1, col0), dot(row2,col0),
            dot(row0, col1), dot(row1, col1), dot(row2,col1),
            dot(row0, col2), dot(row1, col2), dot(row2,col2)
        );
    }
}

#endif // GM_MAT3X3_H
