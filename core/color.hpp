#ifndef CM_COLOR_H
#define CM_COLOR_H

#include "vec4.hpp"

namespace gm {
    
    struct Color
    {
#ifdef _MSC_VER
		union { struct { uint8_t b, g, r, a; }; uint32_t AlignmentDummy; };
#else
        union { struct{ uint8_t r, g, b, a; }; uint32_t AlignmentDummy; };
#endif
        uint32_t& buffer() { return *((uint32_t*)this); };
        gm_vec4<float> vec4() { return gm_vec4<float>(r/255.0f, g/255.0f, b/255.0f, a/255.0f); };

        Color() = default;
        Color(const uint32_t& b):AlignmentDummy(b) {}
        Color(const gm_vec3<float>& v3):r(v3.r*255),g(v3.g*255),b(v3.b*255),a(255) {}
        Color(const gm_vec4<float>& v4):r(v4.r*255),g(v4.g*255),b(v4.b*255),a(v4.a*255) {}
    };

    inline static std::ostream& operator << (std::ostream &os, const Color &c){
        using namespace std;
        os << setprecision(GM_OUTPUT_PRECISION)
           << setw(GM_OUTPUT_WIDTH)
           << GM_OUTPUT_POINT_CMD << GM_OUTPUT_FIXED_CMD
           <<"RGBA( " << c.r << ", " << c.g << ", " << c.b << ", " << c.a << ")";

        return os;
    }

}

#endif // CM_COLOR_H
