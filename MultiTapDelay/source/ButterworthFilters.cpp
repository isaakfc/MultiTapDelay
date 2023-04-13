//
//  ButterworthFilters.cpp
//  MultiTapDelay
//
//  Created by Isaac Faraz-Chandler on 11/04/2023.
//

#include "ButterworthFilters.hpp"

void ButterworthLowPassFilter::updateCoefs(double cutoff)
{
    
    double normalisedCutoff = (M_PI * cutoff) / mSampleRate;
    double c = 1/(tan(normalisedCutoff));
    mB0 = 1.0 / (1.0 + M_SQRT2 * c + pow(c, 2.0));
    mB1 = 2.0 * mB0;
    mB2 = mB0;
    mA0 = 2.0 * mB0 * ( 1.0 - pow(c, 2.0));
    mA1 = mB0 * (1.0 - M_SQRT2 * c + pow(c, 2.0));
}

ButterworthLowPassFilter::ButterworthLowPassFilter(double cutoff, int sampleRate)
{
    mSampleRate = sampleRate;
    updateCoefs(cutoff);
}


void ButterworthHighPassFilter::updateCoefs(double cutoff)
{
    
    double normalisedCutoff = (M_PI * cutoff) / mSampleRate;
    double c = tan(normalisedCutoff);
    mB0 = 1.0 / (1.0 + M_SQRT2 * c + pow(c, 2.0));
    mB1 = -2.0 * mB0;
    mB2 = mB0;
    mA0 = 2.0 * mB0 * (pow(c, 2.0) - 1.0);
    mA1 = mB0 * (1.0 - M_SQRT2 * c + pow(c, 2.0));
}

ButterworthHighPassFilter::ButterworthHighPassFilter(double cutoff, int sampleRate)
{
    mSampleRate = sampleRate;
    updateCoefs(cutoff);
}
