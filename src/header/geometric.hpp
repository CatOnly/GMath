#ifndef GEOMETRIC_H
#define GEOMETRIC_H

#include <math.h>

#include "vec4.hpp"
#include "mat3x3.hpp"
#include "mat4x4.hpp"

namespace gm {

    // -- tools -------------------------
    template<typename T>
    gm_vec3<T> row(gm_mat3<T> mat, int index) {
        return gm_vec3<T>(mat[0][index], mat[1][index], mat[2][index]);
    }

    template<typename T>
    gm_vec4<T> row(gm_mat4<T> mat, int index) {
        return gm_vec4<T>(mat[0][index], mat[1][index], mat[2][index], mat[3][index]);
    }

    template<typename T>
    T distance(const gm_vec3<T> &vFrom, const gm_vec3<T> &vTo) {
        T disX = vTo.x - vFrom.x;
        T disY = vTo.y - vFrom.y;
        T disZ = vTo.z - vFrom.z;

        return static_cast<T>(sqrt(disX*disX +  disY*disY + disZ*disZ));\
    }

    template<typename T>
    T distance(const gm_vec4<T> &vFrom, const gm_vec4<T> &vTo) {
        T disX = vTo.x - vFrom.x;
        T disY = vTo.y - vFrom.y;
        T disZ = vTo.z - vFrom.z;
        T disW = vTo.w - vFrom.w;

        return static_cast<T>(sqrt(disX*disX +  disY*disY + disZ*disZ + disW*disW));\
    }
    // -- vector * matrix --------------
    template<typename T>
    gm_mat3<T> operator * (const gm_vec3<T> &v3, const gm_mat3<T> &m3) {
        T col0Sum = m3[0][0] + m3[0][1] + m3[0][2];
        T col1Sum = m3[1][0] + m3[1][1] + m3[1][2];
        T col2Sum = m3[2][0] + m3[2][1] + m3[2][2];

        gm_vec3<T> colSum = gm_vec3<T>(col0Sum, col1Sum, col2Sum);

        return gm_mat3<T>(v3.x * colSum, v3.y * colSum, v3.z * colSum);
    }

    template<typename T>
    gm_mat4<T> operator * (const gm_vec4<T> &v4, const gm_mat4<T> &m4) {
        T col0Sum = m4[0][0] + m4[0][1] + m4[0][2] + m4[0][3];
        T col1Sum = m4[1][0] + m4[1][1] + m4[1][2] + m4[1][3];
        T col2Sum = m4[2][0] + m4[2][1] + m4[2][2] + m4[2][3];
        T col3Sum = m4[3][0] + m4[3][1] + m4[3][2] + m4[3][3];

        gm_vec4<T> colSum = gm_vec4<T>(col0Sum, col1Sum, col2Sum, col3Sum);

        return gm_mat4<T>(v4.x * colSum, v4.y * colSum, v4.z * colSum, v4.w * colSum);
    }

    // -- matrix * vector --------------
    template<typename T>
    gm_vec3<T> operator * (const gm_mat3<T> &mat, const gm_vec3<T> &col) {
        return gm_vec3<T>(
            dot(row(mat, 0), col), 
            dot(row(mat, 1), col), 
            dot(row(mat, 2), col)
        );
    }

    template<typename T>
    gm_vec4<T> operator * (const gm_mat4<T> &mat, const gm_vec4<T> &col) {
        return gm_vec4<T>(
            dot(row(mat, 0), col), 
            dot(row(mat, 1), col), 
            dot(row(mat, 2), col), 
            dot(row(mat, 3), col)
        );
    }

    // -- matrix * matrix --------------
    template<typename T>
    gm_mat3<T> operator * (const gm_mat3<T> &matL, const gm_mat3<T> &matR) {
        gm_vec3<T> row0 = row(matL, 0);
        gm_vec3<T> row1 = row(matL, 1);
        gm_vec3<T> row2 = row(matL, 2);

        const gm_vec3<T> &col0 = matR[0];
        const gm_vec3<T> &col1 = matR[1];
        const gm_vec3<T> &col2 = matR[2];

        return gm_mat3<T>(
            dot(row0, col0), dot(row1, col0), dot(row2,col0),
            dot(row0, col1), dot(row1, col1), dot(row2,col1),
            dot(row0, col2), dot(row1, col2), dot(row2,col2)
        );
    }

    template<typename T>
    gm_mat4<T> operator * (const gm_mat4<T> &matL, const gm_mat4<T> &matR) {
        gm_vec4<T> row0 = row(matL, 0);
        gm_vec4<T> row1 = row(matL, 1);
        gm_vec4<T> row2 = row(matL, 2);
        gm_vec4<T> row3 = row(matL, 3);

        const gm_vec4<T> &col0 = matR[0];
        const gm_vec4<T> &col1 = matR[1];
        const gm_vec4<T> &col2 = matR[2];
        const gm_vec4<T> &col3 = matR[3];

        return gm_mat4<T>(
            dot(row0,col0), dot(row1,col0), dot(row2,col0), dot(row3,col0),
            dot(row0,col1), dot(row1,col1), dot(row2,col1), dot(row3,col1),
            dot(row0,col2), dot(row1,col2), dot(row2,col2), dot(row3,col2),
            dot(row0,col3), dot(row1,col3), dot(row2,col3), dot(row3,col3)
        );
    }

    // -- base functions ----------------
    template<typename T>
    T length(const gm_vec3<T> &v){
        return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    }

    template<typename T>
    T length(const gm_vec4<T> &v){
        return sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
    }

    template<typename T>
    T dot(const gm_vec3<T> &vL, const gm_vec3<T> &vR) {
        return vL.x * vR.x + vL.y * vR.y + vL.z * vR.z;
    }

    template<typename T>
    T dot(const gm_vec4<T> &vL, const gm_vec4<T> &vR) {
        return vL.x * vR.x + vL.y * vR.y + vL.z * vR.z + vL.w * vR.w;
    }

    template<typename T>
    gm_vec3<T> cross(const gm_vec3<T> &vL, const gm_vec3<T> &vR) {
        return gm_vec3<T>(
            vL.y * vR.z - vL.z * vR.y,
            vL.z * vR.x - vL.x * vR.z,
            vL.x * vR.y - vL.y * vR.x
        );
    }

    template<typename T>
    gm_vec3<T> normalize(const gm_vec3<T> &v) {
        T avg = length(v);
        return gm_vec3<T>(v.x/avg, v.y/avg, v.z/avg);
    }

    template<typename T>
    gm_vec4<T> normalize(const gm_vec4<T> &v) {
        T avg = length(v);
        return gm_vec4<T>(v.x/avg, v.y/avg, v.z/avg, v.w/avg);
    }

    template<typename T>
    gm_mat3<T> transport(const gm_mat3<T> &m) {
        return gm_mat3<T>(
            row(m, 0), 
            row(m, 1), 
            row(m, 2)
        );
    }

    template<typename T>
    gm_mat4<T> transport(const gm_mat4<T> &m) {
        return gm_mat4<T>(
            row(m, 0), 
            row(m, 1), 
            row(m, 2),
            row(m, 3)
        );
    }
}
#endif // GEOMETRIC_H
