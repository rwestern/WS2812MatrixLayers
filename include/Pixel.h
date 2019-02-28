#ifndef _PIXEL_H_
#define _PIXEL_H_

#include <stdint.h>
#include <limits>

class Pixel
{
public:
    typedef uint8_t colourchannel_t;
    typedef uint8_t opacity_t;
    opacity_t opacity = std::numeric_limits<opacity_t>::max();
    colourchannel_t red = 0, green = 0, blue = 0;
};

#endif