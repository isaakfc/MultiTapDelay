//
//  BiquadFilter.cpp
//  MultiTapDelay
//
//  Created by Isaac Faraz-Chandler on 11/04/2023.
//

#include "BiquadFilter.hpp"
#include <iostream>


double BiquadFilter::process(double input)
{
    double x = input;
    double y = mB0 * x + mB1 * x1 + mB2 * x2 - mA0 * y1 - mA1 * y2;
    x2 = x1;
    x1 = x;
    y2 = y1;
    y1 = y;
    return y;
}

