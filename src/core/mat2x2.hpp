#ifndef GM_MAT2X2_H
#define GM_MAT2X2_H

#include "vec2.hpp"
#include "mat.hpp"

namespace gm {

    template<typename T> class gm_mat2
    {
        gm_vec2<T> _column[2];

    public:
        gm_mat2(const gm_vec2<T> &col1, const gm_vec2<T> &col2){
            _column[0] = col1;
            _column[1] = col2;
        }

        gm_mat2(const gm_mat2<T> &m) {
            _column[0] = m[0];
            _column[1] = m[1];
        }

        gm_mat2(const T x1, const T x2,
                const T y1, const T y2){
            _column[0] = gm_vec2<T>(x1, x2);
            _column[1] = gm_vec2<T>(y1, y2);
        }
        gm_mat2(const T x, const T y):gm_mat2(static_cast<T>(x), static_cast<T>(0),
                                              static_cast<T>(0), static_cast<T>(y)){}
        explicit gm_mat2(const gm_vec2<T> &v):gm_mat2(v.x, v.y){}
        explicit gm_mat2(const T value = static_cast<T>(1)):gm_mat2(value, value){}

        gm_mat2<T> operator - () const {
            return gm_mat2<T>(
                -_column[0],
                -_column[1]
            );
        }

        GM_MAT_OPERATOR_INDEX(2)

        GM_MAT_OPERATOR_BASE(2, +)
        GM_MAT_OPERATOR_BASE(2, -)

        GM_MAT_OPERATOR_SELF(2, +=)
        GM_MAT_OPERATOR_SELF(2, -=)

        GM_MAT_OPERATOR_NUM_LEFT(2, +)
        GM_MAT_OPERATOR_NUM_LEFT(2, -)
        GM_MAT_OPERATOR_NUM_LEFT(2, *)
        GM_MAT_OPERATOR_NUM_LEFT(2, /)

        GM_MAT_OPERATOR_SELF_NUM_LEFT(2, +=)
        GM_MAT_OPERATOR_SELF_NUM_LEFT(2, -=)
        GM_MAT_OPERATOR_SELF_NUM_LEFT(2, *=)
        GM_MAT_OPERATOR_SELF_NUM_LEFT(2, /=)
    };

    GM_MAT_OPERATOR_NUM_RIGHT(2, +)
    GM_MAT_OPERATOR_NUM_RIGHT(2, -)
    GM_MAT_OPERATOR_NUM_RIGHT(2, *)
    GM_MAT_OPERATOR_NUM_RIGHT(2, /)

    GM_MAT_VALUE_PTR_FROM(2)

    template<typename T>
    std::ostream& operator << (std::ostream &os, const gm_mat2<T> &m){
        using namespace std;
        os << setprecision(GM_OUTPUT_PRECISION)
           << setw(GM_OUTPUT_WIDTH)
           << GM_OUTPUT_POINT;

        for (int i = 0; i < 2; ++i){
            os << m[0][i] << " "
               << m[1][i];
            if (i != 1) os << endl;
        }

        return os;
    }

    template<typename T>
    gm_mat2<T> transport(const gm_mat2<T> &m) {
        return gm_mat2<T>(
            row(m, 0), 
            row(m, 1)
        );
    }

    template<typename T>
    gm_vec2<T> row(gm_mat2<T> m, int index) {
        return gm_vec2<T>(m[0][index], m[1][index]);
    }

    // -- vector * matrix --------------
    template<typename T>
    gm_mat2<T> operator * (const gm_vec2<T> &v, const gm_mat2<T> &m) {
        T col0Sum = m[0][0] + m[0][1];
        T col1Sum = m[1][0] + m[1][1];

        gm_vec2<T> colSum = gm_vec2<T>(col0Sum, col1Sum);

        return gm_mat2<T>(v.x * colSum, v.y * colSum);
    }

    // -- matrix * vector --------------
    template<typename T>
    gm_vec2<T> operator * (const gm_mat2<T> &m, const gm_vec2<T> &col) {
        return gm_vec2<T>(
            dot(row(m, 0), col),
            dot(row(m, 1), col)
        );
    }

    // -- matrix * matrix --------------
    template<typename T>
    gm_mat2<T> operator * (const gm_mat2<T> &mL, const gm_mat2<T> &mR) {
        gm_vec2<T> row0 = row(mL, 0);
        gm_vec2<T> row1 = row(mL, 1);

        const gm_vec2<T> &col0 = mR[0];
        const gm_vec2<T> &col1 = mR[1];

        return gm_mat2<T>(
            dot(row0, col0), dot(row1, col0),
            dot(row0, col1), dot(row1, col1)
        );
    }
}

#endif // GM_MAT2X2_H
