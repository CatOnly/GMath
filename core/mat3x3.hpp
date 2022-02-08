#ifndef GM_MAT3X3_H
#define GM_MAT3X3_H

#include "vec3.hpp"
#include "mat2x2.hpp"

namespace gm {

    template<typename T> class gm_mat4;
    template<typename T> class gm_mat3
    {
        gm_vec3<T> _column[3];        

    public:
        gm_mat3(const gm_vec3<T> &col1, const gm_vec3<T> &col2, const gm_vec3<T> &col3){
            _column[0] = col1;
            _column[1] = col2;
            _column[2] = col3;
        }
        
        gm_mat3(const gm_mat2<T> &m2){
            _column[0] = gm_vec3<T>(m2[0]);
            _column[1] = gm_vec3<T>(m2[1]);
            _column[2] = gm_vec3<T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(1));
        }

        gm_mat3(const gm_mat3<T> &m3) {
            _column[0] = m3[0];
            _column[1] = m3[1];
            _column[2] = m3[2];
        }
        
        gm_mat3(const gm_mat4<T> &m4);

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

		gm_mat3<T>& zero()
		{
			std::memset(&(_column[0][0]), 0, sizeof(T) * 9);

			return *this;
		}
		gm_mat3<T>& unit()
		{
            *this = gm_mat3<T>(1.0, 1.0, 1.0);

			return *this;
		}

		gm_mat3<T>& scale(const gm_vec2<T> &v) {
			_column[0] *= v.x;
			_column[1] *= v.y;

			return *this;
		}
        
        // Rotate around with axis Z, clockwise, angle start from Y+
		gm_mat3<T>& rotate(const T angle) {
            T a = GM_RADIANS(angle);
            T const c = gm::cos(a);
            T const s = gm::sin(a);
            
            gm_mat3<T> rotate(
                c, -s, 0,
                s,  c, 0,
                0,  0, 1
            );
            
            *this = rotate * (*this);

			return *this;
		}

		gm_mat3<T>& translate(const gm_vec2<T> &v) {
            _column[2] += _column[0] * v.x + _column[1] * v.y;
			return *this;
		}

		inline gm_vec3<T> row(int index) const {
			return gm_vec3<T>(_column[0][index], _column[1][index], _column[2][index]);
		}

		inline gm_mat3<T> transpose() const {
			return gm_mat3<T>(
				row(0),
				row(1),
				row(2)
			);
		}
        
        inline T det() const {
            return   _column[0][0] * (_column[1][1] * _column[2][2] - _column[1][2] * _column[2][1])
                   - _column[0][1] * (_column[1][0] * _column[2][2] - _column[1][2] * _column[2][0])
                   + _column[0][2] * (_column[1][0] * _column[2][1] - _column[1][1] * _column[2][0]);
        }
        
        gm_mat3<T> inverse() const {
            T Determinant = det();

            return gm_mat3<T>(
                          (_column[1][1] * _column[2][2] - _column[2][1] * _column[1][2]) / Determinant,
                        - (_column[1][0] * _column[2][2] - _column[2][0] * _column[1][2]) / Determinant,
                          (_column[1][0] * _column[2][1] - _column[2][0] * _column[1][1]) / Determinant,
                        - (_column[0][1] * _column[2][2] - _column[2][1] * _column[0][2]) / Determinant,
                          (_column[0][0] * _column[2][2] - _column[2][0] * _column[0][2]) / Determinant,
                        - (_column[0][0] * _column[2][1] - _column[2][0] * _column[0][1]) / Determinant,
                          (_column[0][1] * _column[1][2] - _column[1][1] * _column[0][2]) / Determinant,
                        - (_column[0][0] * _column[1][2] - _column[1][0] * _column[0][2]) / Determinant,
                          (_column[0][0] * _column[1][1] - _column[1][0] * _column[0][1]) / Determinant
                   );
        }

		gm_mat3<T> inverseTranspose() const {
            T Determinant = det();

			gm_mat3<T> Inverse;
			Inverse[0][0] = +(_column[1][1] * _column[2][2] - _column[2][1] * _column[1][2]);
			Inverse[0][1] = -(_column[1][0] * _column[2][2] - _column[2][0] * _column[1][2]);
			Inverse[0][2] = +(_column[1][0] * _column[2][1] - _column[2][0] * _column[1][1]);
			Inverse[1][0] = -(_column[0][1] * _column[2][2] - _column[2][1] * _column[0][2]);
			Inverse[1][1] = +(_column[0][0] * _column[2][2] - _column[2][0] * _column[0][2]);
			Inverse[1][2] = -(_column[0][0] * _column[2][1] - _column[2][0] * _column[0][1]);
			Inverse[2][0] = +(_column[0][1] * _column[1][2] - _column[1][1] * _column[0][2]);
			Inverse[2][1] = -(_column[0][0] * _column[1][2] - _column[1][0] * _column[0][2]);
			Inverse[2][2] = +(_column[0][0] * _column[1][1] - _column[1][0] * _column[0][1]);

			for (int i = 0; i < 3; ++i) {
				for (int j = 0; j < 3; ++j) {
					Inverse[i][j] /= Determinant;
				}
			}

			return Inverse;
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
           << GM_OUTPUT_POINT_CMD << GM_OUTPUT_FIXED_CMD;

        for (int i = 0; i < 3; ++i){
            os << m[0][i] << " "
               << m[1][i] << " "
               << m[2][i];
            if (i != 2) os << endl;
        }

        return os;
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
    gm_vec3<T> operator * (const gm_mat3<T> &m, const gm_vec3<T> &v) {
        return gm_vec3<T>(
            m.row(0).dot(v),
            m.row(1).dot(v),
            m.row(2).dot(v)
        );
    }

    // -- matrix * matrix --------------
    template<typename T>
    gm_mat3<T> operator * (const gm_mat3<T> &matL, const gm_mat3<T> &matR) {
        gm_vec3<T> row0 = matL.row(0);
        gm_vec3<T> row1 = matL.row(1);
        gm_vec3<T> row2 = matL.row(2);

        const gm_vec3<T> &col0 = matR[0];
        const gm_vec3<T> &col1 = matR[1];
        const gm_vec3<T> &col2 = matR[2];

        return gm_mat3<T>(
            row0.dot(col0), row1.dot(col0), row2.dot(col0),
            row0.dot(col1), row1.dot(col1), row2.dot(col1),
            row0.dot(col2), row1.dot(col2), row2.dot(col2)
        );
    }
}

#include "mat3x3.inl"

#endif // GM_MAT3X3_H
