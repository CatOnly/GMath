#ifndef GMATH_H
#define GMATH_H

#include "header/debug.hpp"
#include "header/transform.hpp"

/**
 * Default is Right-handed coordinate
 * Switch to Left-handed coordinate, open this macro
 */
// #define GM_USE_COORDINATE_LEFTHAND

namespace gm {

    // -- types ---------------------
    typedef gm_vec3<int> ivec3;
    typedef gm_vec4<int> ivec4;

    typedef gm_vec3<float> vec3;
    typedef gm_vec4<float> vec4;
    typedef gm_quaternion<float> quaternion;

    typedef gm_mat3<float> mat3;
    typedef gm_mat4<float> mat4;


// -- tmp test code -------------
// gm::vec4 a(1.0);
// gm::vec4 b(2.0);
// gm::vec4 c;

// c++;
// --c;
// c = c + 1.0f;
// c = 1.0f - c;
// c += a;
// c += 1.0f;
// //        gm::print(c);
// gm::mat3 move(1,0,0, 0,1,0, 0, 1, 1);
// gm::mat3 rotate(0,1,0, -1,0,0, 0,0,1);
// move *= rotate;

// //        gm::print(move);
// gm::mat3 origin(1,0,0,
//                  0,1,0,
//                  1,0,1);
// gm::mat3 mirror(-1,0,0,
//                  0,1,0,
//                  0,0,1);

// gm::print(origin * mirror);

// double result = 3.14159265358979323846 / 180.0;
// std::cout << "radio = " << result << std::endl;

}

#endif // GMATH_H
