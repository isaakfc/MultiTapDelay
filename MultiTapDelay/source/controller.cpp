//------------------------------------------------------------------------
// Copyright(c) 2023 Semblance.
//------------------------------------------------------------------------

#include "controller.h"
#include "cids.h"


using namespace Steinberg;

namespace MultiTapDelay {

//------------------------------------------------------------------------
// MultiTapDelayController Implementation
//------------------------------------------------------------------------
tresult PLUGIN_API MultiTapDelayController::initialize (FUnknown* context)
{
	// Here the Plug-in will be instantiated

	//---do not forget to call parent ------
	tresult result = EditControllerEx1::initialize (context);
	if (result != kResultOk)
	{
		return result;
	}
    
	// Here you could register some parameters
    Vst::Parameter* mixParam = new Vst::RangeParameter(STR16 ("Mix"),MultiTapParams::kParamMixId,STR16 ("%"), 0, 100, 0);
    Vst::Parameter* mainTapTime = new Vst::RangeParameter(STR16 ("Main Tap Time"),MultiTapParams::kParamMainTapTime,STR16 ("Ms"), 0, 3000, 1500);
    
    //tap times
    Steinberg::Vst::StringListParameter* tap2Time =
    new Steinberg::Vst::StringListParameter(STR16 ("Type"),MultiTapParams::kParamTap2Time);
    tap2Time->appendString(STR16 ("1/16"));
    tap2Time->appendString(STR16 ("1/8"));
    tap2Time->appendString(STR16 ("1/4"));
    tap2Time->appendString(STR16 ("1/2"));
    tap2Time->appendString(STR16 ("1/1"));
    
    Steinberg::Vst::StringListParameter* tap3Time =
    new Steinberg::Vst::StringListParameter(STR16 ("Type"),MultiTapParams::kParamTap3Time);
    tap3Time->appendString(STR16 ("1/16"));
    tap3Time->appendString(STR16 ("1/8"));
    tap3Time->appendString(STR16 ("1/4"));
    tap3Time->appendString(STR16 ("1/1"));
    
    Steinberg::Vst::StringListParameter* tap4Time =
    new Steinberg::Vst::StringListParameter(STR16 ("Type"),MultiTapParams::kParamTap4Time);
    tap4Time->appendString(STR16 ("1/16"));
    tap4Time->appendString(STR16 ("1/8"));
    tap4Time->appendString(STR16 ("1/4"));
    tap4Time->appendString(STR16 ("1/1"));
    
    // Tap gain
    
    Vst::Parameter* mainTapGain = new Vst::RangeParameter(STR16 ("Main Tap Gain"),MultiTapParams::kParamMainTapGain,STR16 ("Db"), -60, -12.05, -60);
    Vst::Parameter* tap2Gain = new Vst::RangeParameter(STR16 ("Tap 2 Gain"),MultiTapParams::kParamTap2Gain,STR16 ("Db"), -60, -12.05, -60);
    Vst::Parameter* tap3Gain = new Vst::RangeParameter(STR16 ("Tap 3 Gain"),MultiTapParams::kParamTap3Gain,STR16 ("Db"), -60, -12.05, -60);
    Vst::Parameter* tap4Gain = new Vst::RangeParameter(STR16 ("Tap 4 Gain"),MultiTapParams::kParamTap4Gain,STR16 ("Db"), -60, -12.05, -60);
    
    // Tap Feedback
    
    Vst::Parameter* mainTapFb = new Vst::RangeParameter(STR16 ("Main Tap Feedback"),MultiTapParams::kParamMainTapFeedback,STR16 ("%"), 0, 1, 0.5);
    Vst::Parameter* tap2Fb = new Vst::RangeParameter(STR16 ("Tap 2 Feedback"),MultiTapParams::kParamTap2Feedback,STR16 ("%"), 0, 1, 0.5);
    Vst::Parameter* tap3Fb = new Vst::RangeParameter(STR16 ("Tap 3 Feedback"),MultiTapParams::kParamTap3Feedback,STR16 ("%"), 0, 1, 0.5);
    Vst::Parameter* tap4Fb = new Vst::RangeParameter(STR16 ("Tap 4 Feedback"),MultiTapParams::kParamTap4Feedback,STR16 ("%"), 0, 1, 0.5);
    
    // Distortion
    Vst::Parameter* distortionLevel = new Vst::RangeParameter(STR16 ("Tape Distortion"),MultiTapParams::KParamTapeSaturation,STR16 ("%"), 1, 3, 1);
    
    Steinberg::Vst::StringListParameter* SaturationActive =
    new Steinberg::Vst::StringListParameter(STR16 ("Saturation Active"),MultiTapParams::KParamSarurationButton);
    SaturationActive->appendString(STR16 ("Off"));
    SaturationActive->appendString(STR16 ("On"));

    
    
    
    // EQ
    
    Vst::Parameter* EqLevel = new Vst::RangeParameter(STR16 ("Tape EQ Level"),MultiTapParams::kParamTapeEQLevel,STR16 ("Db"), 0, 10, 0);
    
    Vst::Parameter* warmth = new Vst::RangeParameter(STR16 ("Warmth"),MultiTapParams::kWarmth,nullptr, 0, 1, 0);
    
    // Wow & Flutter
    
//    Vst::Parameter* wfDepth = new Vst::RangeParameter(STR16 ("Wow & Flutter Depth"),MultiTapParams::kParamTapeWowFlutterDepth,STR16 ("Ms"), 0, 100, 0);
//
//    Vst::Parameter* wfFreq = new Vst::RangeParameter(STR16 ("Wow & Flutter Depth"),MultiTapParams::kParamTapeWowFlutterFreq,STR16 ("Hz"), 0, 100, 0);
    
    
    
    
    parameters.addParameter(mixParam);
    parameters.addParameter(mainTapTime);
    parameters.addParameter(tap2Time);
    parameters.addParameter(tap3Time);
    parameters.addParameter(tap4Time);
    parameters.addParameter(mainTapGain);
    parameters.addParameter(tap2Gain);
    parameters.addParameter(tap3Gain);
    parameters.addParameter(tap4Gain);
    parameters.addParameter(mainTapFb);
    parameters.addParameter(tap2Fb);
    parameters.addParameter(tap3Fb);
    parameters.addParameter(tap4Fb);
    parameters.addParameter(distortionLevel);
    parameters.addParameter(SaturationActive);
    parameters.addParameter(EqLevel);
    parameters.addParameter(warmth);
//    parameters.addParameter(wfDepth);
//    parameters.addParameter(wfFreq);
    
    
    
    

    return kResultTrue;
}

//------------------------------------------------------------------------
tresult PLUGIN_API MultiTapDelayController::terminate ()
{
	// Here the Plug-in will be de-instantiated, last possibility to remove some memory!

	//---do not forget to call parent ------
	return EditControllerEx1::terminate ();
}

//------------------------------------------------------------------------
tresult PLUGIN_API MultiTapDelayController::setComponentState (IBStream* state)
{
	// Here you get the state of the component (Processor part)
	if (!state)
		return kResultFalse;

	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API MultiTapDelayController::setState (IBStream* state)
{
	// Here you get the state of the controller

	return kResultTrue;
}

//------------------------------------------------------------------------
tresult PLUGIN_API MultiTapDelayController::getState (IBStream* state)
{
	// Here you are asked to deliver the state of the controller (if needed)
	// Note: the real state of your plug-in is saved in the processor

	return kResultTrue;
}

//------------------------------------------------------------------------
IPlugView* PLUGIN_API MultiTapDelayController::createView (FIDString name)
{
	// Here the Host wants to open your editor (if you have one)
	if (FIDStringsEqual (name, Vst::ViewType::kEditor))
	{
		// create your editor here and return a IPlugView ptr of it
        return nullptr;
	}
	return nullptr;
}

//------------------------------------------------------------------------
tresult PLUGIN_API MultiTapDelayController::setParamNormalized (Vst::ParamID tag, Vst::ParamValue value)
{
	// called by host to update your parameters
	tresult result = EditControllerEx1::setParamNormalized (tag, value);
	return result;
}

//------------------------------------------------------------------------
tresult PLUGIN_API MultiTapDelayController::getParamStringByValue (Vst::ParamID tag, Vst::ParamValue valueNormalized, Vst::String128 string)
{
	// called by host to get a string for given normalized value of a specific parameter
	// (without having to set the value!)
	return EditControllerEx1::getParamStringByValue (tag, valueNormalized, string);
}

//------------------------------------------------------------------------
tresult PLUGIN_API MultiTapDelayController::getParamValueByString (Vst::ParamID tag, Vst::TChar* string, Vst::ParamValue& valueNormalized)
{
	// called by host to get a normalized value from a string representation of a specific parameter
	// (without having to set the value!)
	return EditControllerEx1::getParamValueByString (tag, string, valueNormalized);
}

//------------------------------------------------------------------------
} // namespace MultiTapDelay
