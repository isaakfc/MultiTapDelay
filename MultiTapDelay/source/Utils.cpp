//
//  Utils.cpp
//  MultiTapDelay
//
//  Created by Isaac Faraz-Chandler on 06/04/2023.
//


#include "Utils.hpp"
#include <cmath>

float arctanDistortion(float in, float alpha)
{
    return (2/M_PI)*atan(in*alpha);
}


float dbToRawAmp(float in)
{
    return pow(10, in/20);
}

