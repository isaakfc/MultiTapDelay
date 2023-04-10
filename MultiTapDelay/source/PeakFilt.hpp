//
//  PeakFilt.hpp
//  MultiTapDelay
//
//  Created by Isaac Faraz-Chandler on 08/04/2023.
//

#pragma once
#include <cmath>

class PeakFiltBoost
{
    
public:
    PeakFiltBoost(int sampleRate, double cutoffFrequency, double gain, double bandWidth);
    float process(float input);
    void setCoefficients(int sampleRate, double cutoffFrequency, double gain, double bandWidth);

private:
    double mWc;
    double mWb;
    double x1;
    double x2;
    double V0;
    double H0;
    double c;
    double d;
    
    
    
    
    
    
};
