#ifndef GM_MAT4X4_H
#define GM_MAT4X4_H

#include "vec4.hpp"
#include "mat3x3.hpp"

namespace gm {

    template<typename T> class gm_quaternion;
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
        explicit gm_mat4(const gm_mat3<T> &m3){
            _column[0] = gm_vec4<T>(m3[0]);
            _column[1] = gm_vec4<T>(m3[1]);
            _column[2] = gm_vec4<T>(m3[2]);
            _column[3] = gm_vec4<T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1));
        }

        gm_mat4<T>& zero()
        {
            std::memset(&(_column[0][0]), 0, sizeof(T) * 16);
            return *this;
        }

        gm_mat4<T>& unit()
        {
            zero();
            _column[0][0] = 1.0f;
            _column[1][1] = 1.0f;
            _column[2][2] = 1.0f;
            _column[3][3] = 1.0f;

            return *this;
        }

        gm_mat4<T>& scale(const gm_vec3<T> &v) {
            _column[0] *= v.x;
            _column[1] *= v.y;
            _column[2] *= v.z;

            return *this;
        }

        gm_mat4<T>& translate(const gm_vec3<T> &v) {
            _column[3] += _column[0] * v.x + _column[1] * v.y + _column[2] * v.z;

            return *this;
        }

        /* 
         * the order of euler-angle is yaw、pitch、roll
         * 
         * nx*nx*(1-c)+c     ny*nx*(1-c)-s*nz  nz*nx*(1-c)+s*ny  0
         * nx*ny*(1-c)+s*nz  ny*ny*(1-c)+c     nz*ny*(1-c)-s*nx  0
         * nx*nz*(1-c)-s*ny  ny*nz*(1-c)+s*nx  nz*nz*(1-c)+c     0
         * 0                 0                 0                 1
         *
         * see http://docs.gl/gl2/glRotate
         */ 
        gm_mat4<T>& rotate(const T angle, const gm_vec3<T> &v3) {
            T a = GM_RADIANS(angle);
            T const c = std::cos(a);
            T const s = std::sin(a);

            gm_vec3<T> axis(v3.normalize());
            gm_vec3<T> temp((T(1) - c) * axis);
            gm_mat4<T> rotate;
            rotate[0][0] = c + temp[0] * axis[0];
            rotate[0][1] = temp[0] * axis[1] + s * axis[2];
            rotate[0][2] = temp[0] * axis[2] - s * axis[1];

            rotate[1][0] = temp[1] * axis[0] - s * axis[2];
            rotate[1][1] = c + temp[1] * axis[1];
            rotate[1][2] = temp[1] * axis[2] + s * axis[0];

            rotate[2][0] = temp[2] * axis[0] + s * axis[1];
            rotate[2][1] = temp[2] * axis[1] - s * axis[0];
            rotate[2][2] = c + temp[2] * axis[2];

            gm_vec4<T> col0 = _column[0] * rotate[0][0] + _column[1] * rotate[0][1] + _column[2] * rotate[0][2];
            gm_vec4<T> col1 = _column[0] * rotate[1][0] + _column[1] * rotate[1][1] + _column[2] * rotate[1][2];
            gm_vec4<T> col2 = _column[0] * rotate[2][0] + _column[1] * rotate[2][1] + _column[2] * rotate[2][2];
            _column[0] = col0;
            _column[1] = col1;
            _column[2] = col2;

            return *this;
        }

		gm_vec4<T> row(int index) const {
			return gm_vec4<T>(_column[0][index], _column[1][index], _column[2][index], _column[3][index]);
		}

		gm_mat4<T> transport() const {
			return gm_mat4<T>(
				row(0),
				row(1),
				row(2),
				row(3)
			);
		}

		gm_mat4<T> operator - () const {
			return gm_mat4<T>(
				-_column[0],
				-_column[1],
				-_column[2],
				-_column[3]
			);
		}

		GM_MAT_OPERATOR_INDEX(4)

		GM_MAT_OPERATOR_BASE(4, +)
		GM_MAT_OPERATOR_BASE(4, -)

		GM_MAT_OPERATOR_SELF(4, +=)
		GM_MAT_OPERATOR_SELF(4, -=)

		GM_MAT_OPERATOR_NUM_LEFT(4, +)
		GM_MAT_OPERATOR_NUM_LEFT(4, -)
		GM_MAT_OPERATOR_NUM_LEFT(4, *)
		GM_MAT_OPERATOR_NUM_LEFT(4, / )

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
           << GM_OUTPUT_POINT_CMD << GM_OUTPUT_FIXED_CMD;

        for (int i = 0; i < 4; ++i) {
            os << m[0][i] << " "
               << m[1][i] << " "
               << m[2][i] << " "
               << m[3][i];
            if (i != 3) os << endl;
        }

        return os;
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
			mat.row(0).dot(col),
			mat.row(1).dot(col),
			mat.row(2).dot(col),
			mat.row(3).dot(col)
        );
    }

    // -- matrix * matrix --------------
    template<typename T>
    gm_mat4<T> operator * (const gm_mat4<T> &matL, const gm_mat4<T> &matR) {
        gm_vec4<T> row0 = matL.row(0);
        gm_vec4<T> row1 = matL.row(1);
        gm_vec4<T> row2 = matL.row(2);
        gm_vec4<T> row3 = matL.row(3);

        const gm_vec4<T> &col0 = matR[0];
        const gm_vec4<T> &col1 = matR[1];
        const gm_vec4<T> &col2 = matR[2];
        const gm_vec4<T> &col3 = matR[3];

        return gm_mat4<T>(
            row0.dot(col0), row1.dot(col0), row2.dot(col0), row3.dot(col0),
            row0.dot(col1), row1.dot(col1), row2.dot(col1), row3.dot(col1),
            row0.dot(col2), row1.dot(col2), row2.dot(col2), row3.dot(col2),
            row0.dot(col3), row1.dot(col3), row2.dot(col3), row3.dot(col3)
        );
    }
}

#include "mat4x4.inl"

#endif // GM_MAT4X4_H
