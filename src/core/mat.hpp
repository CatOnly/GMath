#ifndef GM_MAT_H
#define GM_MAT_H

#define GM_MAT_VALUE_PTR_FROM(size)\
template<typename T>\
const T *valuePtrFrom(const gm_mat##size<T> &m) {\
    return &(m[0][0]);\
}

#define GM_MAT_OPERATOR_INDEX(size) \
gm_vec##size<T>& operator[](int i) {\
    assert(i >= 0 && i < size);\
    return _column[i];\
}\
gm_vec##size<T> const& operator[](int i) const {\
    assert(i >= 0 && i < size);\
    return _column[i];\
}

#define GM_MAT_OPERATOR_BASE(size, symbol)\
gm_mat##size<T> operator symbol (const gm_mat##size<T> &m){\
    gm_mat##size<T> mTmp;\
    for (int i = 0; i < size; ++i){\
        mTmp[i] = _column[i] symbol m[i];\
    }\
\
    return mTmp;\
}
#define GM_MAT_OPERATOR_SELF(size, symbol)\
gm_mat##size<T>& operator symbol (const gm_mat##size<T> &m){\
    for (int i = 0; i < size; ++i){\
        _column[i] symbol m[i];\
    }\
\
    return *this;\
}

#define GM_MAT_OPERATOR_NUM_LEFT(size, symbol)\
gm_mat##size<T> operator symbol (const T value){\
    gm_mat##size<T> mTmp;\
    for (int i = 0; i < size; ++i){\
        mTmp[i] = _column[i] symbol value;\
    }\
\
    return mTmp;\
}

#define GM_MAT_OPERATOR_NUM_RIGHT(size, symbol)\
template<typename T>\
gm_mat##size<T> operator symbol (const T value, const gm_mat##size<T> &mat){\
    gm_mat##size<T> mTmp;\
    for (int i = 0; i < size; ++i){\
        mTmp[i] = mat[i] symbol value;\
    }\
\
    return mTmp;\
}

#define GM_MAT_OPERATOR_SELF_NUM_LEFT(size, symbol)\
gm_mat##size<T> & operator symbol (const T &value){\
    for (int i = 0; i < size; ++i){\
        _column[i] symbol value;\
    }\
\
    return *this;\
}

#endif // GM_MAT_H
