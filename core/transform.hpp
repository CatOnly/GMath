#ifndef GM_TRANSFORM_H
#define GM_TRANSFORM_H

#include "quaternion.hpp"

namespace gm {

    template <typename T> class gm_transform2D
    {
    public:
        gm_vec2<T> scale;
        gm_vec2<T> translate;
        gm_vec2<T> rotate;
        
    public:
        gm_transform2D() : scale(1), translate(0), rotate() {};
        gm_transform2D(const gm_transform2D<T>& t) {
            translate = t.translate;
            scale = t.scale;
            rotate = t.rotate;
        }
        
        gm_mat3<T> matrix2(bool isRotateFirst = true)
        {
            gm_mat3<T> m3;
            m3.identity();
            if (isRotateFirst)
            {
//               m3.rotate(rotate.y, AXIS_V2_X);
               m3.translate(translate);
            }
            else
            {
               m3.translate(translate);
//               m3.rotate(rotate.y, AXIS_V2_X);
            }
            
            return m3;
        }
        
        bool operator==(const gm_transform2D<T>& t) const
        {
            return (t.scale == scale && t.translate == translate && t.rotate == rotate);
        }
    };

    template <typename T> class gm_transform3D
    {
    public:
        gm_vec3<T> scale;
        gm_vec3<T> translate;
        gm_quaternion<T> rotate;
        
    public:
        gm_transform3D() : scale(1), translate(0), rotate() {};
        gm_transform3D(const gm_transform3D<T>& t) {
            translate = t.translate;
            scale = t.scale;
            rotate = t.rotate;
        }
        
        gm_mat4<T> matrix4NoScale(bool isRotateFirst = true)
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
        
        gm_mat4<T> matrix4(bool isRotateFirst = true)
        {
            return matrix4NoScale(isRotateFirst).scale(scale);
        }
        
        bool operator==(const gm_transform2D<T>& t) const
        {
            return (t.scale == scale && t.translate == translate && t.rotate == rotate);
        }
        
    };

}

#endif /* GM_TRANSFORM_H */
