#ifndef GMATH_H
#define GMATH_H

#include "header/debug.hpp"
#include "header/transform.hpp"

namespace gm {

    // -- types ---------------------
    typedef gm_vec3<int> ivec3;
    typedef gm_vec4<int> ivec4;

    typedef gm_vec3<float> vec3;
    typedef gm_vec4<float> vec4;
    typedef gm_mat3<float> mat3;
    typedef gm_mat4<float> mat4;

// SFL::vec4 a(1.0);
// SFL::vec4 b(2.0);
// SFL::vec4 c;

// c++;
// --c;
// c = c + 1.0f;
// c = 1.0f - c;
// c += a;
// c += 1.0f;
// //        SFL::print(c);
// SFL::mat3 move(1,0,0, 0,1,0, 0, 1, 1);
// SFL::mat3 rotate(0,1,0, -1,0,0, 0,0,1);
// move *= rotate;

// //        SFL::print(move);
// SFL::mat3 origin(1,0,0,
//                  0,1,0,
//                  1,0,1);
// SFL::mat3 mirror(-1,0,0,
//                  0,1,0,
//                  0,0,1);

// SFL::print(origin * mirror);

// double result = 3.14159265358979323846 / 180.0;
// std::cout << "radio = " << result << std::endl;

}

#endif // GMATH_H
