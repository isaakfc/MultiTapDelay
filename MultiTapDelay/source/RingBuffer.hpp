//
//  RingBuffer.hpp
//  MultiTapDelay
//
//  Created by Isaac Faraz-Chandler on 05/04/2023.
//

#pragma once
#include <vector>


class RingBuffer{
public:
    RingBuffer(int size);
    double read(int delay);
    void write(double val);
    void reset(int size, int pos);
    double readInterp(double delay);
    double readInterp3(double delay);
private:
    std::vector<double> mBuffer;
    int mPos;
};

