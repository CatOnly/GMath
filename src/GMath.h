#ifndef SGLMATH_H
#define SGLMATH_H

#include "debug.hpp"
#include "geometric.hpp"

namespace SFL {

    // -- types ---------------------
    typedef sfl_vec3<int> ivec3;
    typedef sfl_vec4<int> ivec4;

    typedef sfl_vec3<float> vec3;
    typedef sfl_vec4<float> vec4;
    typedef sfl_mat3<float> mat3;
    typedef sfl_mat4<float> mat4;


    // -- value left multiply vector or matrix ---------------------
    template<typename T> sfl_vec3<T> operator + (const T &, const sfl_vec3<T> &);
    template<typename T> sfl_vec3<T> operator - (const T &, const sfl_vec3<T> &);
    template<typename T> sfl_vec3<T> operator * (const T &, const sfl_vec3<T> &);
    template<typename T> sfl_vec3<T> operator / (const T &, const sfl_vec3<T> &);

    template<typename T> sfl_vec4<T> operator + (const T &, const sfl_vec4<T> &);
    template<typename T> sfl_vec4<T> operator - (const T &, const sfl_vec4<T> &);
    template<typename T> sfl_vec4<T> operator * (const T &, const sfl_vec4<T> &);
    template<typename T> sfl_vec4<T> operator / (const T &, const sfl_vec4<T> &);

    template<typename T> sfl_mat3<T> operator + (const T &, const sfl_mat3<T> &);
    template<typename T> sfl_mat3<T> operator - (const T &, const sfl_mat3<T> &);
    template<typename T> sfl_mat3<T> operator * (const T &, const sfl_mat3<T> &);
    template<typename T> sfl_mat3<T> operator / (const T &, const sfl_mat3<T> &);

    template<typename T> sfl_mat4<T> operator + (const T &, const sfl_mat4<T> &);
    template<typename T> sfl_mat4<T> operator - (const T &, const sfl_mat4<T> &);
    template<typename T> sfl_mat4<T> operator * (const T &, const sfl_mat4<T> &);
    template<typename T> sfl_mat4<T> operator / (const T &, const sfl_mat4<T> &);


    // -- vector left multiply matrix ---------------------
    template<typename T> sfl_mat3<T> operator * (const sfl_vec3<T> &, const sfl_mat3<T> &);
    template<typename T> sfl_mat4<T> operator * (const sfl_vec4<T> &, const sfl_mat4<T> &);
}

// 模版声明和定义不能分开 故 include
#include "SGLMath.cpp"

#endif // SGLMATH_H
