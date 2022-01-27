#include "mat2x2.hpp"
#include "mat3x3.hpp"

namespace gm {
    
    template<typename T>
    gm_mat2<T>::gm_mat2(const gm_mat3<T> &m)
    {
        _column[0][0] = m[0][0];
        _column[0][1] = m[0][1];
        _column[1][0] = m[1][0];
        _column[1][1] = m[1][1];
    }
    
} // namespace gm 
