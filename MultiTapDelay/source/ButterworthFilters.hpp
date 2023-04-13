//
//  ButterworthFilters.hpp
//  MultiTapDelay
//
//  Created by Isaac Faraz-Chandler on 11/04/2023.
//

#pragma once
#include "BiquadFilter.hpp"
#include <cmath>


class ButterworthLowPassFilter: public BiquadFilter
{
public:
    ButterworthLowPassFilter(double cutoff, int sampleRate);
    void updateCoefs(double cutoff) override;
};


class ButterworthHighPassFilter: public BiquadFilter
{
public:
    ButterworthHighPassFilter(double cutoff, int sampleRate);
    void updateCoefs(double cutoff) override;
};
