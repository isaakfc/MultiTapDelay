//
//  BiquadFilter.hpp
//  MultiTapDelay
//
//  Created by Isaac Faraz-Chandler on 11/04/2023.
//

#pragma once

#include "Filter.hpp"



class BiquadFilter: public Filter
{
public:
    double process(double input) override;
    void setNormalizedCoefficients(double b0, double b1, double b2, double a0, double a1, double a2);
protected:
    double mB0, mB1, mB2;
    double mA0, mA1;
    double x1, x2;
    double y1, y2;
};

