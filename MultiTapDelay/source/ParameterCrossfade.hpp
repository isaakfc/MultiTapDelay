//
//  ParameterCrossfade.hpp
//  MultiTapDelay
//
//  Created by Isaac Faraz-Chandler on 13/04/2023.
//

#pragma once

#include <iostream>
#include <cmath>

class ParameterCrossfade
{
public:
    ParameterCrossfade(double sampleRate, double fadeInTime, double fadeOutTime, float initialParameterValue, float threshold);
    void parameterChanged(float parameterValue);
    float process(float input);
    float ignoreLargeChange(float parameterValue);

private:
    float gainChangePerSampleFI;
    float gainChangePerSampleFO;
    float currentGain;
    double previousParameterValues[20];
    double previousParameterValue;
    int arrayIndex;
    bool changedFlag;
    float mThreshold;
};
