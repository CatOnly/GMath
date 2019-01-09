#ifndef GMCONFIG_H
#define GMCONFIG_H

#define GM_OUTPUT_WIDTH 0
#define GM_OUTPUT_PRECISION 2
#define GM_OUTPUT_FIXED

#define GM_RIGHT_HANDED 0
#define GM_LEFT_HANDED  1
#define GM_USE_COORDINATE GM_RIGHT_HANDED

#define GM_DEBUG_ON  1
#define GM_DEBUG_OFF 0
#define GM_DEBUG GM_DEBUG_ON

// dependent define
#if GM_OUTPUT_PRECISION > 0
#define GM_OUTPUT_POINT_CMD showpoint
#else
#define GM_OUTPUT_POINT_CMD noshowpoint
#endif

#ifdef GM_OUTPUT_FIXED
#define GM_OUTPUT_FIXED_CMD fixed
#else
#define GM_OUTPUT_FIXED_CMD ""
#endif

#endif // GMCONFIG_H
