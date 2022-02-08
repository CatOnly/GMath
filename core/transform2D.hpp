#ifndef GM_TRANSFORM_2D_H
#define GM_TRANSFORM_2D_H

#include "quaternion.hpp"

namespace gm {

    template <typename T> class gm_transform2D
    {
    public:
        T rotate;
        gm_vec2<T> scale;
        gm_vec2<T> translate;
        
    public:
        gm_transform2D() : rotate(0), scale(1), translate(0) {};
        gm_transform2D(const gm_transform2D<T>& t) : rotate(t.rotate), scale(t.scale), translate(t.translate) {};
        
        bool operator==(const gm_transform2D<T>& t) const
        {
            return (t.scale == scale && t.translate == translate && t.rotate == rotate);
        }
        
        gm_mat3<T> matrix3NoScale(bool isRotateFirst = true)
        {
            gm_mat3<T> m3(1.0, 1.0, 1.0);
            if (isRotateFirst)
            {
                m3.rotate(rotate);
                m3.translate(translate);
            }
            else
            {
                m3.translate(translate);
                m3.rotate(rotate);
            }
            
            return m3;
        }
        
        gm_mat3<T> matrix3(bool isRotateFirst = true)
        {
            return matrix3NoScale(isRotateFirst).scale(scale);
        }
        
    };

} // namespace gm

#endif /* GM_TRANSFORM_2D_H */
