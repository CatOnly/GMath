#ifndef GMCONFIG_H
#define GMCONFIG_H

#define GM_OUTPUT_WIDTH 0
#define GM_OUTPUT_PRECISION 2

#if GM_OUTPUT_PRECISION > 0
#define GM_OUTPUT_POINT showpoint
#else
#define GM_OUTPUT_POINT noshowpoint
#endif

#define GM_RIGHT_HANDED 0
#define GM_LEFT_HANDED  1
#define GM_USE_COORDINATE GM_RIGHT_HANDED

#define GM_DEBUG_ON  1
#define GM_DEBUG_OFF 0
#define GM_DEBUG GM_DEBUG_ON


#endif // GMCONFIG_H
