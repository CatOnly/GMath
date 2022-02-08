#ifndef GM_TRANSFORM_H
#define GM_TRANSFORM_H

#include "transform2D.hpp"

namespace gm {

    template <typename T> class gm_transform3D
    {
    public:
        gm_vec3<T> rotate;
        gm_vec3<T> scale;
        gm_vec3<T> translate;
        
    public:
        gm_transform3D() : scale(1), translate(0), rotate() {};
        gm_transform3D(const gm_transform3D<T>& t) : scale(t.scale), translate(t.translate), rotate(t.rotate) {};
        
        bool operator==(const gm_transform2D<T>& t) const
        {
            return (t.scale == scale && t.translate == translate && t.rotate == rotate);
        }
        
        gm_mat4<T> matrix4NoScale(bool isRotateFirst = true)
        {
            gm_mat4<T> m4(1.0, 1.0, 1.0, 1.0);
            if (isRotateFirst)
            {
                m4 = gm_quaternion<T>(rotate.pitch, rotate.yaw, rotate.roll).mat4() * m4;
                m4.translate(translate);
            }
            else
            {
                m4.translate(translate);
                m4 = gm_quaternion<T>(rotate.pitch, rotate.yaw, rotate.roll).mat4() * m4;
            }
            
            return m4;
        }
        
        gm_mat4<T> matrix4(bool isRotateFirst = true)
        {
            return matrix4NoScale(isRotateFirst).scale(scale);
        }
        
        
    };


} // namespace gm

#endif // GM_TRANSFORM_H
