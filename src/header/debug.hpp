#ifndef DEBUG_H
#define DEBUG_H

#include "vec3.hpp"
#include "vec4.hpp"
#include "mat3x3.hpp"
#include "mat4x4.hpp"

namespace SFL {

    // -- print vector -----------------------
    template<typename T>
    void print(const sfl_vec3<T> &vec){
        using namespace std;
        cout << "Vector3:  " << showpoint
             << vec.x << " "
             << vec.y << " "
             << vec.z << " "
             << endl;
    }

    template<typename T>
    void print(const sfl_vec4<T> &vec){
        using namespace std;
        cout << "Vector4:  " << showpoint
             << vec.x << " "
             << vec.y << " "
             << vec.z << " "
             << vec.w << " "
             << endl;
    }

    // -- print matrix -----------------------
    template<typename T>
    void print(const sfl_mat3<T> &matrix){
        using namespace std;
        cout << "Matrix3: " << endl;
        cout.precision(3);
        for (int i = 0; i < 3; ++i){
            cout << showpoint
                 << matrix[0][i] << " "
                 << matrix[1][i] << " "
                 << matrix[2][i] << " "
                 << endl;
        }
    }

    template<typename T>
    void print(const sfl_mat4<T> &matrix){
        using namespace std;
        cout << "Matrix4: " << endl;
        cout.precision(3);
        for (int i = 0; i < 4; ++i){
            cout << showpoint
                 << matrix[0][i] << " "
                 << matrix[1][i] << " "
                 << matrix[2][i] << " "
                 << matrix[3][i] << " "
                 << endl;
        }
    }

}

#endif // DEBUG_H
