#ifndef GM_TRANSFORM_2D_H
#define GM_TRANSFORM_2D_H

#include "quaternion.hpp"

namespace gm {

	const static gm_vec2<float> ZERO_V2(0.0f, 0.0f);
	const static gm_vec2<float> AXIS_X_V2(1.0f, 0.0f);
	const static gm_vec2<float> AXIS_Y_V2(0.0f, 1.0f);

    const static gm_vec3<float> ZERO(0.0f, 0.0f, 0.0f);
    const static gm_vec3<float> AXIS_X(1.0f, 0.0f, 0.0f);
    const static gm_vec3<float> AXIS_Y(0.0f, 1.0f, 0.0f);
    const static gm_vec3<float> AXIS_Z(0.0f, 0.0f, 1.0f);

    template <typename T> class gm_transform2D
    {
    public:
        gm_vec2<T> scale;
        gm_vec2<T> rotate;
        gm_vec2<T> translate;
        
    public:
        gm_transform2D() : scale(1), translate(0), rotate() {};
        gm_transform2D(const gm_transform2D<T>& t) : scale(t.scale), translate(t.translate), rotate(t.rotate) {};
        
        gm_mat3<T> matrix2(bool isRotateFirst = true)
        {
            gm_mat3<T> m3;
            m3.identity();
            if (isRotateFirst)
            {
                m3.rotate(rotate.y, AXIS_X_V2);
                m3.translate(translate);
            }
            else
            {
                m3.translate(translate);
                m3.rotate(rotate.y, AXIS_Y_V2);
            }
            
            return m3;
        }
        
        bool operator==(const gm_transform2D<T>& t) const
        {
            return (t.scale == scale && t.translate == translate && t.rotate == rotate);
        }
    };

} // namespace gm

#endif /* GM_TRANSFORM_2D_H */
