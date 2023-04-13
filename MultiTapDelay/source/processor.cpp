//------------------------------------------------------------------------
// Copyright(c) 2023 Semblance.
//------------------------------------------------------------------------

#include "processor.h"
#include "cids.h"

#include "base/source/fstreamer.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"
#include "public.sdk/source/vst/vstaudioprocessoralgo.h"
#include "Utils.hpp"
#include <iostream>


using namespace Steinberg;

namespace MultiTapDelay {
//------------------------------------------------------------------------
// MultiTapDelayProcessor
//------------------------------------------------------------------------
MultiTapDelayProcessor::MultiTapDelayProcessor ()
{
	//--- set the wanted controller for our processor
	setControllerClass (kMultiTapDelayControllerUID);
}

//------------------------------------------------------------------------
MultiTapDelayProcessor::~MultiTapDelayProcessor ()
{}

//------------------------------------------------------------------------
tresult PLUGIN_API MultiTapDelayProcessor::initialize (FUnknown* context)
{
	// Here the Plug-in will be instantiated
	
	//---always initialize the parent-------
	tresult result = AudioEffect::initialize (context);
	// if everything Ok, continue
	if (result != kResultOk)
	{
		return result;
	}

	//--- create Audio IO ------
	addAudioInput (STR16 ("Stereo In"), Steinberg::Vst::SpeakerArr::kStereo);
	addAudioOutput (STR16 ("Stereo Out"), Steinberg::Vst::SpeakerArr::kStereo);

	/* If you don't need an event bus, you can remove the next line */
	addEventInput (STR16 ("Event In"), 1);

	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API MultiTapDelayProcessor::terminate ()
{
	// Here the Plug-in will be de-instantiated, last possibility to remove some memory!
	
	//---do not forget to call parent ------
	return AudioEffect::terminate ();
}

//------------------------------------------------------------------------
tresult PLUGIN_API MultiTapDelayProcessor::setActive (TBool state)
{
	//--- called when the Plug-in is enable/disable (On/Off) -----
    Steinberg::Vst::SpeakerArrangement arr ;
    if (getBusArrangement (Steinberg::Vst::kOutput, 0, arr) != kResultTrue)
    return kResultFalse ;
    int numChannels = Steinberg::Vst::SpeakerArr :: getChannelCount (arr );
    double sampleRate = processSetup.sampleRate;


    
    if(state)
    {
        rbufferVec.clear();
        pFiltVec.clear();
        
        for (int i = 0; i < numChannels; i++)
        {
            rbufferVec.push_back(RingBuffer(6 * processSetup.sampleRate));
            pFiltVec.push_back(PeakFiltBoost(processSetup.sampleRate, 100, mPFiltGain, 100));
            LowPassVec.push_back(ButterworthLowPassFilter(20000, processSetup.sampleRate));
            HighPassVec.push_back(ButterworthHighPassFilter(0, processSetup.sampleRate));
            LowPassVec.push_back(ButterworthLowPassFilter(20000, processSetup.sampleRate));
            HighPassVec.push_back(ButterworthHighPassFilter(0, processSetup.sampleRate));
            pCrossfade.push_back(ParameterCrossfade(processSetup.sampleRate, 5 , 0.2, mDelay1Time, 0.0001));
            
        }
    
    
    }
    
    delayValues[0] = mDelay1Time * 1.0625;
    delayValues[1] = mDelay1Time * 1.125;
    delayValues[2] = mDelay1Time * 1.25;
    delayValues[3] = mDelay1Time * 1.5;
    delayValues[4] = mDelay1Time * 2;
	return AudioEffect::setActive (state);
}



void MultiTapDelayProcessor::handleParameterChanges (Steinberg::Vst::IParameterChanges* changes)
{
    if (changes)
    {
        // for each parameter defined by its ID
        int32 numParamsChanged = changes->getParameterCount ();
        for (int32 index = 0; index < numParamsChanged; index++)
        {
            // for this parameter we could iterate the list of value changes (could 1 per audio block or more!)
            // in this example we get only the last value (getPointCount - 1)
            Vst::IParamValueQueue* paramQueue = changes->getParameterData (index);
            if (paramQueue)
            {
                Vst::ParamValue value;
                int32 sampleOffset;
                int32 numPoints = paramQueue->getPointCount ();
                switch (paramQueue->getParameterId ())
                {
                    case MultiTapParams::kParamMixId:
                        if (paramQueue->getPoint (numPoints - 1, sampleOffset, value) == kResultTrue)
                            mMix = value;
                            break;
                    case MultiTapParams::kParamMainTapTime:
                        if (paramQueue->getPoint (numPoints - 1, sampleOffset, value) == kResultTrue)
                            mDelay1Time = 0 + value * (3000);
                            delayValues[0] = mDelay1Time * 1.0625;
                            delayValues[1] = mDelay1Time * 1.125;
                            delayValues[2] = mDelay1Time * 1.25;
                            delayValues[3] = mDelay1Time * 1.5;
                            delayValues[4] = mDelay1Time * 2;
                            break;
                    case MultiTapParams::kParamTap2Time:
                        if (paramQueue->getPoint (numPoints - 1, sampleOffset, value) == kResultTrue)
                            mDelay2Time = value * 4;
                            break;
                    case MultiTapParams::kParamTap3Time:
                        if (paramQueue->getPoint (numPoints - 1, sampleOffset, value) == kResultTrue)
                            mDelay3Time = value * 4;
                            break;
                    case MultiTapParams::kParamTap4Time:
                        if (paramQueue->getPoint (numPoints - 1, sampleOffset, value) == kResultTrue)
                            mDelay4Time = value * 4;
                            break;
                    case MultiTapParams::kParamMainTapGain:
                        if (paramQueue->getPoint (numPoints - 1, sampleOffset, value) == kResultTrue)
                            mDelay1Gain = -60 + value*(-12.05 - -60);
                            mDelay1Gain = dbToRawAmp(mDelay1Gain);
                            break;
                    case MultiTapParams::kParamTap2Gain:
                        if (paramQueue->getPoint (numPoints - 1, sampleOffset, value) == kResultTrue)
                            mDelay2Gain = -60 + value*(-12.05 - -60);
                            mDelay2Gain = dbToRawAmp(mDelay2Gain);
                            break;
                    case MultiTapParams::kParamTap3Gain:
                        if (paramQueue->getPoint (numPoints - 1, sampleOffset, value) == kResultTrue)
                            mDelay3Gain = -60 + value*(-12.05 - -60);
                            mDelay3Gain = dbToRawAmp(mDelay3Gain);
                            break;
                    case MultiTapParams::kParamTap4Gain:
                        if (paramQueue->getPoint (numPoints - 1, sampleOffset, value) == kResultTrue)
                            mDelay4Gain = -60 + value*(-12.05 - -60);
                            mDelay4Gain = dbToRawAmp(mDelay4Gain);
                            break;
                    case MultiTapParams::kParamMainTapFeedback:
                        if (paramQueue->getPoint (numPoints - 1, sampleOffset, value) == kResultTrue)
                            mDelay1Fb = value * (0.25);
                            break;
                    case MultiTapParams::kParamTap2Feedback:
                        if (paramQueue->getPoint (numPoints - 1, sampleOffset, value) == kResultTrue)
                            mDelay2Fb = value * (0.25);
                            break;
                    case MultiTapParams::kParamTap3Feedback:
                        if (paramQueue->getPoint (numPoints - 1, sampleOffset, value) == kResultTrue)
                            mDelay3Fb = value * (0.25);
                            break;
                    case MultiTapParams::kParamTap4Feedback:
                        if (paramQueue->getPoint (numPoints - 1, sampleOffset, value) == kResultTrue)
                            mDelay4Fb = value * (0.25);
                            break;
                    case MultiTapParams::KParamTapeSaturation:
                        if (paramQueue->getPoint (numPoints - 1, sampleOffset, value) == kResultTrue)
                            mDistortionAmount = 1 + value*(3 - 1);
                            break;
                    case MultiTapParams::KParamSarurationButton:
                        if (paramQueue->getPoint (numPoints - 1, sampleOffset, value) == kResultTrue)
                            mSaturationActive = value;
                            break;
                    case MultiTapParams::kParamTapeEQLevel:
                        if (paramQueue->getPoint (numPoints - 1, sampleOffset, value) == kResultTrue)
                            mPFiltGain =  value * 10.0;
                            pFiltVec.at(0).setCoefficients(processSetup.sampleRate, 100, mPFiltGain, 100);
                            pFiltVec.at(1).setCoefficients(processSetup.sampleRate, 100, mPFiltGain, 100);
                            break;
                    case MultiTapParams::kWarmth:
                        if (paramQueue->getPoint (numPoints - 1, sampleOffset, value) == kResultTrue)
                            mWarmthHigh= value * 70;
                            mWarmthLow = 20000 + value*(10000 - 20000);
                            LowPassVec.at(0).updateCoefs(mWarmthLow);
                            LowPassVec.at(1).updateCoefs(mWarmthLow);
                            LowPassVec.at(2).updateCoefs(mWarmthLow);
                            LowPassVec.at(3).updateCoefs(mWarmthLow);
                            HighPassVec.at(0).updateCoefs(mWarmthHigh);
                            HighPassVec.at(1).updateCoefs(mWarmthHigh);
                            HighPassVec.at(2).updateCoefs(mWarmthHigh);
                            HighPassVec.at(3).updateCoefs(mWarmthHigh);
                }
            }
        }
    }
    
}


 

//------------------------------------------------------------------------
tresult PLUGIN_API MultiTapDelayProcessor::process (Vst::ProcessData& data)
{
	//--- First : Read inputs parameter changes-----------


    
    
    handleParameterChanges (data.inputParameterChanges);
    
    //-- Flush case: we only need to update parameter, noprocessing possible
    if (data.numInputs == 0 || data.numSamples == 0)
        return kResultOk;

    //--- Here you have to implement your processing
    int32 numChannels = data.inputs[0].numChannels;

    //---get audio buffers using helper-functions(vstaudioprocessoralgo.h)-------------
    uint32 sampleFramesSize = getSampleFramesSizeInBytes(processSetup, data.numSamples);
    void** in = getChannelBuffersPointer (processSetup, data.inputs[0]);
    void** out = getChannelBuffersPointer (processSetup, data.outputs[0]);

    // Here could check the silent flags
    // now we will produce the output
    // mark our outputs has not silent
    data.outputs[0].silenceFlags = 0;

   
    // for each channel (left and right)
    for (int32 i = 0; i < numChannels; i++)
    {
        int32 samples = data.numSamples;
        Vst::Sample32* ptrIn = (Vst::Sample32*)in[i];
        Vst::Sample32* ptrOut = (Vst::Sample32*)out[i];
        Vst::Sample32 tmp;
        int sampleCount = 0;
        pCrossfade[i].parameterChanged(mDelay1Time);
        // for each sample in this channel
        while (--samples >= 0)
        {

            // apply gain
            double processedDelayVal =  pCrossfade[i].ignoreLargeChange(mDelay1Time);
            double delay1InSamples = processSetup.sampleRate * (processedDelayVal / 1000);
            double delay2InSamples = processSetup.sampleRate * (delayValues[mDelay2Time] / 1000);
            double delay3InSamples = processSetup.sampleRate * (delayValues[mDelay3Time] / 1000);
            double delay4InSamples = processSetup.sampleRate * (delayValues[mDelay4Time] / 1000);
            double delayed = (rbufferVec[i].readInterp(delay1InSamples) * mDelay1Gain) + (rbufferVec[i].readInterp(delay2InSamples) * mDelay2Gain) + (rbufferVec[i].readInterp(delay3InSamples) * mDelay3Gain) + (rbufferVec[i].readInterp(delay4InSamples) * mDelay4Gain);
            float current = (*ptrIn++);
            rbufferVec[i].write(current + (mDelay1Fb * rbufferVec[i].readInterp(delay1InSamples)) + (mDelay2Fb * rbufferVec[i].readInterp(delay2InSamples)) + (mDelay3Fb * rbufferVec[i].readInterp(delay3InSamples)) + (mDelay4Fb * rbufferVec[i].readInterp(delay4InSamples)));
            if (mSaturationActive)
            {
                delayed = arctanDistortion(delayed, mDistortionAmount);
            }
            delayed = pFiltVec[i].process(delayed);
            if (mWarmthHigh > 0)
            {
                delayed = LowPassVec[i].process(delayed);
                delayed = LowPassVec[i+2].process(delayed);
                delayed = HighPassVec[i].process(delayed);
                delayed = HighPassVec[i+2].process(delayed);
            }
            
            current = pCrossfade[i].process(delayed);
            tmp = mMix * delayed + (1 - mMix) * current;
            (*ptrOut++) = tmp;
//            (*ptrOut++) = (*ptrIn++);
            sampleCount++;
        }
        

    }
            
          
    
    //--- Here you have to implement your processing

    return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API MultiTapDelayProcessor::setupProcessing (Vst::ProcessSetup& newSetup)
{
	//--- called before any processing ----
	return AudioEffect::setupProcessing (newSetup);
}

//------------------------------------------------------------------------
tresult PLUGIN_API MultiTapDelayProcessor::canProcessSampleSize (int32 symbolicSampleSize)
{
	// by default kSample32 is supported
	if (symbolicSampleSize == Vst::kSample32)
		return kResultTrue;

	// disable the following comment if your processing support kSample64
	/* if (symbolicSampleSize == Vst::kSample64)
		return kResultTrue; */

	return kResultFalse;
}

//------------------------------------------------------------------------
tresult PLUGIN_API MultiTapDelayProcessor::setState (IBStream* state)
{
	// called when we load a preset, the model has to be reloaded
	IBStreamer streamer (state, kLittleEndian);
	
	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API MultiTapDelayProcessor::getState (IBStream* state)
{
	// here we need to save the model
	IBStreamer streamer (state, kLittleEndian);

	return kResultOk;
}

//------------------------------------------------------------------------
} // namespace MultiTapDelay
