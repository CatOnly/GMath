#ifndef GM_TRANSFORM_H
#define GM_TRANSFORM_H

#include "quaternion.hpp"

namespace gm {
    
    const static gm_vec2<float> ZERO_V2(0.0f, 0.0f);
    const static gm_vec2<float> AXIS_V2_X(1.0f, 0.0f);
    const static gm_vec2<float> AXIS_V2_Y(0.0f, 1.0f);

    const static gm_vec3<float> ZERO_V3(0.0f, 0.0f, 0.0f);
    const static gm_vec3<float> AXIS_V3_X(1.0f, 0.0f, 0.0f);
    const static gm_vec3<float> AXIS_V3_Y(0.0f, 1.0f, 0.0f);
    const static gm_vec3<float> AXIS_V3_Z(0.0f, 0.0f, 1.0f);

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
        
        gm_mat3<T> matrix2(bool isRotateFirst = true);
        
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
        gm_transform3D(const gm_transform3D<T>& t) : scale(t.scale), translate(t.translate), rotate(t.rotate) {};
        
        gm_mat4<T> matrix4NoScale(bool isRotateFirst = true);
        
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

#include "transform.inl"

#endif /* GM_TRANSFORM_H */
