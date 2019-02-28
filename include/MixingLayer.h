#ifndef _MIXINGLAYER_H_
#define _MIXINGLAYER_H_

#include "BinaryLayer.h"
#include "GfxLayer.h"
#include "MixParameters.h"

class MixingLayer : public BinaryLayer
{
    const GfxLayer& top, bottom;
    const MixParameters mixmethod;
public:
    MixingLayer(const GfxLayer&,
     const GfxLayer&,
     const MixParameters method);
};


#endif