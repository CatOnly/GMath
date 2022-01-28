#ifndef GM_COLOR_H
#define GM_COLOR_H

#include "vec4.hpp"

namespace gm {
    
    struct Color
    {
#ifdef _MSC_VER
		union { struct { uint8_t b, g, r, a; }; uint32_t data; };
#else
        union { struct{ uint8_t r, g, b, a; }; uint32_t data; };
#endif
        uint32_t& buffer() { return *((uint32_t*)this); };
        gm_vec4<float> vec4() { return gm_vec4<float>(r, g, b, a); };

        Color() = default;
        Color(const uint32_t& b):data(b) {}
        Color(const gm_vec3<float>& v3):r(v3.r),g(v3.g),b(v3.b),a(255) {}
        Color(const gm_vec4<float>& v4):r(v4.r),g(v4.g),b(v4.b),a(v4.a) {}

		uint8_t & operator[](int i) {
				GM_ASSERT(i >= 0 && i < 4);
				return (&b)[i];
		}
		uint8_t const & operator[](int i) const {
				GM_ASSERT(i >= 0 && i < 4); 
				return (&b)[i]; 
		}
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

#endif // GM_COLOR_H
