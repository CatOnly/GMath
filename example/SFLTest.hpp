#ifndef SFLTEST_HPP
#define SFLTEST_HPP

#include "GMath.hpp"

#define USE_NAMESPACE using namespace std; using namespace gm;
#define TEST_INIT(type) {\
    type a;\
    cout << "Init no param: " << a << endl;\
    type b(2);\
    cout << "Init with param 2: " << b << endl;\
    float varParam = 3.0;\
    const type c(varParam);\
    cout << "Init with variable 3.0: " << c << endl;\
    cout << "Init with const of same type: " << type(c) << endl;\
    cout << "Init with variable of same type: " << type(b) << endl;\
    cout << "Init with temporary variable of same type: " << type(type(9)) << endl;\
}

#define TEST_OPERATOR_NUM(type) {\
    type a(0.6);\
    cout << "a = "<< a << endl;\
    cout << "a + 2.0f = " << a + 2.0f << endl;\
    cout << "a - 2.0f = " << a - 2.0f << endl;\
    cout << "a * 2.0f = " << a * 2.0f << endl;\
    cout << "a / 2.0f = " << a / 2.0f << endl;\
    cout << "2.0f + a = " << 2.0f + a << endl;\
    cout << "2.0f - a = " << 2.0f - a << endl;\
    cout << "2.0f * a = " << 2.0f * a << endl;\
    cout << "2.0f / a = " << 2.0f / a << endl;\
    cout << "a += 2.0f, a = " << (a += 2.0f) << endl;\
    cout << "a -= 2.0f, a = " << (a -= 2.0f) << endl;\
    cout << "a *= 2.0f, a = " << (a *= 2.0f) << endl;\
    cout << "a /= 2.0f, a = " << (a /= 2.0f) << endl;\
}

#define TEST_OPERATOR(type) {\
    type a(0.7);\
    type b(0.2);\
    cout << "a = "<< a << "\nb = " << b << endl;\
    cout << "a + b = " << a + b << endl;\
    cout << "a - b = " << a - b << endl;\
    cout << "a * b = " << a * b << endl;\
    cout << "a / b = " << a / b << endl;\
    cout << "a += b, a = " << (a += b) << endl;\
    cout << "a -= b, a = " << (a -= b) << endl;\
    cout << "a *= b, a = " << (a *= b) << endl;\
    cout << "a /= b, a = " << (a /= b) << endl;\
}

#define TEST_OPERATOR_NEG(type) {\
    type a(0.2);\
    cout << "a = "<< a << endl;\
    cout << "-a = " << -a << endl;\
}

#define TEST_OPERATOR_SELF(type) {\
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
    TEST_INIT(type)\
    TEST_OPERATOR_NEG(type)\
    TEST_OPERATOR_NUM(type)\
    TEST_OPERATOR_SELF(type)\
    TEST_OPERATOR(type)\
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

void testMatrix(){
    USE_NAMESPACE
}

void testMain(){
    testVector();
    testMatrix();
}

#endif // SFLTEST_HPP
