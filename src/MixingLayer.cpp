#include "MixingLayer.h"

MixingLayer::MixingLayer(const GfxLayer& top_,
     const GfxLayer& bottom_,
     const MixParameters method)
: top(top_), bottom(bottom_), mixmethod(method)
{
}