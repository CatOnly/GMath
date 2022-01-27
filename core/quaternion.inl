#include "quaternion.hpp"
#include "mat4x4.hpp"

namespace gm {

    template <typename T>
    gm_quaternion<T>::gm_quaternion(const gm_mat3<T>& m)
    {
        T fourXSquaredMinus1 = m[0][0] - m[1][1] - m[2][2];
        T fourYSquaredMinus1 = m[1][1] - m[0][0] - m[2][2];
        T fourZSquaredMinus1 = m[2][2] - m[0][0] - m[1][1];
        T fourWSquaredMinus1 = m[0][0] + m[1][1] + m[2][2];
        
        int biggestIndex = 0;
        T fourBiggestSquaredMinus1 = fourWSquaredMinus1;
        if(fourXSquaredMinus1 > fourBiggestSquaredMinus1)
        {
            fourBiggestSquaredMinus1 = fourXSquaredMinus1;
            biggestIndex = 1;
        }
        if(fourYSquaredMinus1 > fourBiggestSquaredMinus1)
        {
            fourBiggestSquaredMinus1 = fourYSquaredMinus1;
            biggestIndex = 2;
        }
        if(fourZSquaredMinus1 > fourBiggestSquaredMinus1)
        {
            fourBiggestSquaredMinus1 = fourZSquaredMinus1;
            biggestIndex = 3;
        }

        T biggestVal = sqrt(fourBiggestSquaredMinus1 + T(1)) * T(0.5);
        T mult = T(0.25) / biggestVal;

        switch(biggestIndex)
        {
        case 0:
            w = biggestVal; 
            x = (m[1][2] - m[2][1]) * mult;
            y = (m[2][0] - m[0][2]) * mult;
            z = (m[0][1] - m[1][0]) * mult;
            break;
        case 1:
            w = (m[1][2] - m[2][1]) * mult;
            x = biggestVal;
            y = (m[0][1] + m[1][0]) * mult;
            z = (m[2][0] + m[0][2]) * mult;
            break;
        case 2:
            w = (m[2][0] - m[0][2]) * mult;
            x = (m[0][1] + m[1][0]) * mult;
            y = biggestVal;
            z = (m[1][2] + m[2][1]) * mult;
            break;
        case 3:
            w = (m[0][1] - m[1][0]) * mult;
            x = (m[2][0] + m[0][2]) * mult;
            y = (m[1][2] + m[2][1]) * mult;
            z = biggestVal;
            break;
        }
    }

    template <typename T>
    gm_quaternion<T>::gm_quaternion(const gm_mat4<T>& m);
    {
        gm_quaternion(gm_mat3<T>(m));
    }

    template <typename T>
    gm_mat3<T> gm_quaternion<T>::mat3() const
    {
        float xx = x * x;
        float xy = x * y;
        float xz = x * z;
        float xw = x * w;
        float yy = y * y;
        float yz = y * z;
        float yw = y * w;
        float zz = z * z;
        float zw = z * w;

        gm_mat3<T> m(1);

        m[0][0] = 1 - 2 * (yy + zz);
        m[0][1] = 2 * (xy - zw);
        m[0][2] = 2 * (xz + yw);

        m[1][0] = 2 * (xy + zw);
        m[1][1] = 1 - 2 * (xx + zz);
        m[1][2] = 2 * (yz - xw);

        m[2][0] = 2 * (xz - yw);
        m[2][1] = 2 * (yz + xw);
        m[2][2] = 1 - 2 * (xx + yy);

        return m;
    }

    template <typename T>
    gm_mat4<T> gm_quaternion<T>::mat4() const
    {
        return gm_mat4<T>(mat3());
    }

    template<typename T>
    gm_vec4<T> operator * (const gm_quaternion<T> &q, const gm_vec4<T> &v) const
    {
        return gm_vec4<T>(q * gm_vec3<T>(v), v.w);
    }

    template<typename T>
    gm_vec4<T> operator * (const gm_vec4<T> &v, const gm_quaternion<T> &q) const
    {
        return q.inverse() * v;
    }

} // namespace gm 