#ifndef GM_VEC2_H
#define GM_VEC2_H

#include <cassert>
#include <math.h>
#include <iostream>
#include <iomanip>

#include "config.h"

#define VEC_OPERATOR_INDEX(size)\
T & operator[](int i) { \
    assert(i >= 0 && i < size);\
    return (&x)[i];\
}\
T const & operator[](int i) const { \
    assert(i >= 0 && i < size);\
    return (&x)[i];\
}

namespace gm {
    
}

#endif // GM_VEC2_H
