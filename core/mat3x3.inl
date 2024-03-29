#include "mat4x4.hpp"

namespace gm {
    
    template<typename T>
    gm_mat3<T>::gm_mat3(const gm_mat4<T> &m)
    {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                _column[i][j] = m[i][j];
            }
        }
    }
    
} // namespace gm
