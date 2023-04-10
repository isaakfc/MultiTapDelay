//
//  PeakFilt.cpp
//  MultiTapDelay
//
//  Created by Isaac Faraz-Chandler on 08/04/2023.
//

#include "PeakFilt.hpp"


PeakFiltBoost::PeakFiltBoost(int sampleRate, double cutoffFrequency, double gain, double bandWidth)
{
    setCoefficients(sampleRate, cutoffFrequency, gain, bandWidth);
}


void PeakFiltBoost::setCoefficients(int sampleRate, double cutoffFrequency, double gain, double bandWidth)
{
    mWc = (2 * cutoffFrequency) / sampleRate;
    mWb = (2 * bandWidth) / sampleRate;
    V0 = pow(10, (gain/20));
    H0 = V0 - 1;
    c = (tan(M_PI*mWb/2)-1) / (tan(M_PI*mWb/2)+1);
    d = -cos(M_PI*mWc);
}

float PeakFiltBoost::process(float input)
{
    
    float xhNew = input - d * (1-c) * x1 + c * x2;
    float apY = -c * xhNew + d*(1-c)*x1 + x2;
    x2 = x1;
    x1 = xhNew;
    return 0.5 * H0 * (x1 - apY) + x1;
}
