#include "transform.hpp"
#include "GMath.hpp"

namespace gm {

    template<typename T>
    gm_mat3<T> gm_transform2D<T>::matrix2(bool isRotateFirst /** = true */)
    {
        gm_mat3<T> m3;
        m3.identity();
        if (isRotateFirst)
        {
            m3.rotate(rotate.y, AXIS_V2_X);
            m3.translate(translate);
        }
        else
        {
            m3.translate(translate);
            m3.rotate(rotate.y, AXIS_V2_Y);
        }
        
        return m3;
    }

    template<typename T>
    gm_mat4<T> gm_transform3D<T>::matrix4NoScale(bool isRotateFirst /** = true */)
    {
        gm_mat4<T> m4;
        m4.identity();
        if (isRotateFirst)
        {
//               m4.rotate(rotate.z, AXIS_V3_Z);
            m4.translate(translate);
        }
        else
        {
            m4.translate(translate);
//               m4.rotate(rotate.x, AXIS_V3_X);
        }
        
        return m4;
    }

} // namespace gm
