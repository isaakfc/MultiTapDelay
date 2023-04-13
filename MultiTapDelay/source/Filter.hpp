//
//  Filter.hpp
//  MultiTapDelay
//
//  Created by Isaac Faraz-Chandler on 11/04/2023.
//

#pragma once

class Filter
{
public:
    virtual void updateCoefs(double cutoff) = 0;
    virtual double process(double input) = 0;
    
protected:
    int mSampleRate;
    double mCutoff;
};
