//------------------------------------------------------------------------
// Copyright(c) 2023 Semblance.
//------------------------------------------------------------------------




#pragma once

#include "public.sdk/source/vst/vstaudioeffect.h"
#include "RingBuffer.hpp"
#include "PeakFilt.hpp"



namespace MultiTapDelay {

//------------------------------------------------------------------------
//  MultiTapDelayProcessor
//------------------------------------------------------------------------
class MultiTapDelayProcessor : public Steinberg::Vst::AudioEffect
{
public:
	MultiTapDelayProcessor ();
	~MultiTapDelayProcessor () SMTG_OVERRIDE;

    // Create function
	static Steinberg::FUnknown* createInstance (void* /*context*/) 
	{ 
		return (Steinberg::Vst::IAudioProcessor*)new MultiTapDelayProcessor; 
	}

	//--- ---------------------------------------------------------------------
	// AudioEffect overrides:
	//--- ---------------------------------------------------------------------
	/** Called at first after constructor */
	Steinberg::tresult PLUGIN_API initialize (Steinberg::FUnknown* context) SMTG_OVERRIDE;
	
	/** Called at the end before destructor */
	Steinberg::tresult PLUGIN_API terminate () SMTG_OVERRIDE;
	
	/** Switch the Plug-in on/off */
	Steinberg::tresult PLUGIN_API setActive (Steinberg::TBool state) SMTG_OVERRIDE;

	/** Will be called before any process call */
	Steinberg::tresult PLUGIN_API setupProcessing (Steinberg::Vst::ProcessSetup& newSetup) SMTG_OVERRIDE;
	
	/** Asks if a given sample size is supported see SymbolicSampleSizes. */
	Steinberg::tresult PLUGIN_API canProcessSampleSize (Steinberg::int32 symbolicSampleSize) SMTG_OVERRIDE;

	/** Here we go...the process call */
	Steinberg::tresult PLUGIN_API process (Steinberg::Vst::ProcessData& data) SMTG_OVERRIDE;
    
    void handleParameterChanges (Steinberg::Vst::IParameterChanges* changes);
		
	/** For persistence */
	Steinberg::tresult PLUGIN_API setState (Steinberg::IBStream* state) SMTG_OVERRIDE;
	Steinberg::tresult PLUGIN_API getState (Steinberg::IBStream* state) SMTG_OVERRIDE;

//------------------------------------------------------------------------
protected:
    float mMix = 0;
    float mDelay1Time = 1500;
    int mDelay2Time = 0;
    int mDelay3Time = 0;
    int mDelay4Time = 0;
    float mDelay1Gain = 0;
    float mDelay2Gain = 0;
    float mDelay3Gain = 0;
    float mDelay4Gain = 0;
    float mDelay1Fb = 0;
    float mDelay2Fb = 0;
    float mDelay3Fb = 0;
    float mDelay4Fb = 0;
    float mDistortionAmount = 1;
    float mEqLevel = 0;
    float mFlutterDepth = 0;
    float mFlutterFrequency = 0;
    std::vector<RingBuffer> rbufferVec;
//    std::vector<SincInterpolator> sincInterVec;
    std::vector<PeakFiltBoost> pFiltVec;
    float delayValues[5];
    double mPFiltGain = 0;
    bool mSaturationActive = 0;
    
    


    
    
    
    

};

//------------------------------------------------------------------------
} // namespace MultiTapDelay
