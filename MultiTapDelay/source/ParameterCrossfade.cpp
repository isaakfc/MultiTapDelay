//
//  ParameterCrossfade.cpp
//  MultiTapDelay
//
//  Created by Isaac Faraz-Chandler on 13/04/2023.
//

#include "ParameterCrossfade.hpp"



ParameterCrossfade::ParameterCrossfade(double sampleRate, double fadeInTime, double fadeOutTime, float initialParameterValue, float threshold)
{
    arrayIndex = 0;
    gainChangePerSampleFI = (1 / sampleRate) / fadeInTime;
    gainChangePerSampleFO = (1 / sampleRate) / fadeOutTime;
    
    previousParameterValues[arrayIndex++] = initialParameterValue;
    previousParameterValue = initialParameterValue;
    currentGain = 1;
    mThreshold = threshold;
}

void ParameterCrossfade::parameterChanged(float parameterValue) // float parameterValue
{
    
    changedFlag = 0;
    
    for(int i = 0; i < 19; i++)
    {
    
        if(previousParameterValues[i] != previousParameterValues[i + 1])
        {
            changedFlag = 1;
            break;
        }
        
    }
    
    previousParameterValues[arrayIndex] = parameterValue;
    arrayIndex++;
    arrayIndex = arrayIndex % 20;
    
}

float ParameterCrossfade::process(float input)
{
    
    if (!changedFlag)
    {
        if (currentGain < 1)
        {
            currentGain += gainChangePerSampleFI;
            input *= currentGain;
        }
        else
        {
            currentGain = 1;
        }
    }
    if (changedFlag)
    {
        if (currentGain > 0)
        {
            currentGain -= gainChangePerSampleFO;
            input *= currentGain;
        }
        else
        {
            currentGain = 0;
            input = 0;
        }

    }
    
    return input;
    
}

float ParameterCrossfade::ignoreLargeChange(float parameterValue)
{
    
    for(int i = 0; i < 19; i++)
    {
    
        if(previousParameterValues[i] != previousParameterValues[i + 1])
        {
    
            return previousParameterValue;
    
        }
    }
    
    previousParameterValue = parameterValue;
    return parameterValue;

}





