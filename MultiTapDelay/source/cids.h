//------------------------------------------------------------------------
// Copyright(c) 2023 Semblance.
//------------------------------------------------------------------------

#pragma once

#include "pluginterfaces/base/funknown.h"
#include "pluginterfaces/vst/vsttypes.h"

namespace MultiTapDelay {
//------------------------------------------------------------------------
static const Steinberg::FUID kMultiTapDelayProcessorUID (0x77975A13, 0xF5B35D56, 0x91DE7048, 0x8BF562E2);
static const Steinberg::FUID kMultiTapDelayControllerUID (0x26B78B00, 0x2A7F5EFB, 0x85470D92, 0x1B9D576A);

#define MultiTapDelayVST3Category "Fx"

//------------------------------------------------------------------------
} // namespace MultiTapDelay

enum MultiTapParams : Steinberg::Vst::ParamID
{
    kParamMixId = 102, // should be a unique id...
    kParamMainTapTime = 103,
    kParamTap2Time = 104,
    kParamTap3Time = 105,
    kParamTap4Time = 106,
    kParamMainTapGain = 107,
    kParamTap2Gain = 108,
    kParamTap3Gain = 109,
    kParamTap4Gain = 110,
    kParamMainTapFeedback = 111,
    kParamTap2Feedback = 112,
    kParamTap3Feedback = 113,
    kParamTap4Feedback = 114,
    KParamTapeSaturation = 115,
    KParamSarurationButton = 116,
    kParamTapeEQLevel = 117,
    kParamTapeWowFlutterDepth = 118,
    kParamTapeWowFlutterFreq = 119,
    
};
