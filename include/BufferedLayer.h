#ifndef _BUFFEREDLAYER_H_
#define _BUFFEREDLAYER_H_

#include "GfxLayer.h"
#include <vector>
#include "Pixel.h"
#include "WS2812Buffer.h"

class BufferedLayer : public GfxLayer
{
    WS2812Buffer buffer;
    
public:
    BufferedLayer(const uint8_t height, const uint8_t width);
};


#endif