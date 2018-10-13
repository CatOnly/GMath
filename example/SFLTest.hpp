#ifndef SFLTEST_HPP
#define SFLTEST_HPP

#include "GMath.hpp"

#define USE_NAMESPACE using namespace std; using namespace gm;
#define TEST_INIT(type, str) {\
    type a;\
    cout << "Init no param: " << str << a << endl;\
    type b(2);\
    cout << "Init with param 2: " << str << b << endl;\
    float varParam = 3.0;\
    const type c(varParam);\
    cout << "Init with variable 3.0: " << str << c << endl;\
    cout << "Init with const of same type: " << str << type(c) << endl;\
    cout << "Init with variable of same type: " << str << type(b) << endl;\
    cout << "Init with temporary variable of same type: " << str << type(type(9)) << endl;\
}

#define TEST_OPERATOR_NUM(type, str) {\
    type a(0.6);\
    cout << "a = "<< a << endl;\
    cout << "a + 2.0f = " << str << a + 2.0f << endl;\
    cout << "a - 2.0f = " << str << a - 2.0f << endl;\
    cout << "a * 2.0f = " << str << a * 2.0f << endl;\
    cout << "a / 2.0f = " << str << a / 2.0f << endl;\
    cout << "2.0f + a = " << str << 2.0f + a << endl;\
    cout << "2.0f - a = " << str << 2.0f - a << endl;\
    cout << "2.0f * a = " << str << 2.0f * a << endl;\
    cout << "2.0f / a = " << str << 2.0f / a << endl;\
    cout << "a += 2.0f, a = " << str << (a += 2.0f) << endl;\
    cout << "a -= 2.0f, a = " << str << (a -= 2.0f) << endl;\
    cout << "a *= 2.0f, a = " << str << (a *= 2.0f) << endl;\
    cout << "a /= 2.0f, a = " << str << (a /= 2.0f) << endl;\
}

#define TEST_OPERATOR_NEG(type, str) {\
    type a(0.2);\
    cout <<  "a = " << str << a << endl;\
    cout << "-a = " << str << -a << endl;\
}

#define TEST_VEC_OPERATOR(type) {\
    type a(0.7);\
    type b(0.2);\
    cout << "a = " << a << "\nb = " << b << endl;\
    cout << "a + b = " << a + b << endl;\
    cout << "a - b = " << a - b << endl;\
    cout << "a * b = " << a * b << endl;\
    cout << "a / b = " << a / b << endl;\
    cout << "a += b, a = " << (a += b) << endl;\
    cout << "a -= b, a = " << (a -= b) << endl;\
    cout << "a *= b, a = " << (a *= b) << endl;\
    cout << "a /= b, a = " << (a /= b) << endl;\
}

#define TEST_VEC_OPERATOR_SELF(type) {\
    type a(0.7);\
    cout << "a = "<< a << endl;\
    cout << "++a = " << ++a << endl;\
    cout << "--a = " << --a << endl;\
    cout << "a++ = " << a++ << endl;\
    cout << "a-- = " << a-- << endl;\
    cout << "a = "<< a << endl;\
}

#define TEST_BEGIN_TITLE(type) cout << "\nTest " #type " Begin:" << endl;

#define TEST_VEC_FUNC(type) {\
    type a(2);\
    type b(0.2);\
    cout << "a = "<< a << "\nb = " << b << endl;\
    cout << "length(a) = " << length(a) << endl;\
    cout << "distance(a, b) = " << distance(a, b) << endl;\
    cout << "normalize(a) = " << normalize(a) << endl;\
    cout << "dot(a, b) = " << dot(a, b) << endl;\
}

#define TEST_VEC(type) {\
    TEST_INIT(type,"")\
    TEST_OPERATOR_NEG(type,"")\
    TEST_OPERATOR_NUM(type,"")\
    TEST_VEC_OPERATOR_SELF(type)\
    TEST_VEC_OPERATOR(type)\
    TEST_VEC_FUNC(type)\
}

void testVector(){
    USE_NAMESPACE

    TEST_BEGIN_TITLE(vec2)
    vec2 a2(1.0, 2);
    cout << "Init a with param 1.0, 2: " << a2 << endl;
    cout << "a[1] = " << a2[1] << endl;
    TEST_VEC(vec2)

    TEST_BEGIN_TITLE(vec3)
    vec3 a3(3.0, 0.2, 6);
    cout << "Init a with param 3.0, 0.2, 6: " << a3 << endl;
    cout << "Init b with param (1.0, 2): " << vec3(a2) << endl;
    cout << "a[1] = " << a3[1] << endl;
    TEST_VEC(vec3)
    vec3 va(1,0,0);
    vec3 vb(0,1,0);
    cout << "a = "<< va << "\nb = " << vb << endl;
    cout << "cross(a, b) = " << cross(va, vb) << endl;

    TEST_BEGIN_TITLE(vec4)
    vec4 a4(2, 3.0, 0.2, 6);
    cout << "Init a with param 2, 3.0, 0.2, 6: " << a4 << endl;
    cout << "Init b with param (3.0, 0.2, 6): " << vec4(a3) << endl;
    cout << "a[1] = " << a4[1] << endl;
    TEST_VEC(vec4)
}

#define TEST_MAT_OPERATOR(type) {\
    type a(0.7);\
    type b(0.2);\
    cout << "a = \n" << a << "\nb = \n" << b << endl;\
    cout << "a + b = \n" << a + b << endl;\
    cout << "a - b = \n" << a - b << endl;\
    cout << "a * b = \n" << a * b << endl;\
    cout << "a += b, a = \n" << (a += b) << endl;\
    cout << "a -= b, a = \n" << (a -= b) << endl;\
}

#define TEST_MAT_FUNC \
    cout << "a = \n" << a << "\nv = \n" << v << endl;\
    cout << "row(a, 0) = " << row(a, 0) << endl;\
    cout << "transport(a) = \n" << transport(a) << endl;\
    cout << "a = \n" << a << endl;\
    cout << "a * v = \n" << a * v << endl;\
    cout << "v * a = \n" << v * a << endl;

#define TEST_MAT(type) {\
    TEST_INIT(type,"\n")\
    TEST_OPERATOR_NEG(type,"\n")\
    TEST_OPERATOR_NUM(type,"\n")\
    TEST_MAT_OPERATOR(type)\
}

void testMatrix(){
    USE_NAMESPACE

    TEST_BEGIN_TITLE(mat2)
    {
        mat2 a(1,2,3,4);
        cout << "mat2(1,2,\n3,4) = \n" << a << endl;
    }
    TEST_MAT(mat2);
    {
        mat2 a(1,2,3,4);
        vec2 v(0,1);
        TEST_MAT_FUNC
    }

    TEST_BEGIN_TITLE(mat3)
    {
        mat3 a(1,2,3, 4,5,6, 7,8,9);
        cout << "mat3(1,2,3, 4,5,6, 7,8,9) = \n" << a << endl;
        cout << "mat3(mat2(2,3,2,3)) = \n" << mat3(mat2(2,3,2,3)) << endl;
    }
    TEST_MAT(mat3);
    {
        mat3 a(1,2,3, 4,5,6, 7,8,9);
        vec3 v(0,1,2);
        TEST_MAT_FUNC
    }

    TEST_BEGIN_TITLE(mat4)
    {
        mat4 a(0.1,0.2,0.3,0.4, 0.5,0.6,0.7,0.8, 0.9,1,1.1,1.2, 1.3,1.4,1.5,1.6);
        cout << "mat4(0.1,0.2,0.3,0.4, 0.5,0.6,0.7,0.8, 0.9,1,1.1,1.2, 1.3,1.4,1.5,1.6) = \n" << a << endl;
        cout << "mat4(mat3(1,2,3, 4,5,6, 7,8,9)) = \n" << mat4(mat3(1,2,3, 4,5,6, 7,8,9)) << endl;
    }
    TEST_MAT(mat4);
    {
        mat4 a(0.1,0.2,0.3,0.4, 0.5,0.6,0.7,0.8, 0.9,1,1.1,1.2, 1.3,1.4,1.5,1.6);
        vec4 v(0,1,2,3);
        TEST_MAT_FUNC
    }
}

void testMain(){
    testVector();
    testMatrix();
}

#endif // SFLTEST_HPP
