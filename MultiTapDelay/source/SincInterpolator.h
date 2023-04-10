//
//  SincInterpolator.h
//  MultiTapDelay
//
//  Created by Isaac Faraz-Chandler on 07/04/2023.
//

#ifndef SincInterpolator_h
#define SincInterpolator_h

#include <vector>
#include <cmath>






class SincInterpolator {
public:
    SincInterpolator(double tau, double sampleRate, double windowAlpha)
        : m_tau(tau), m_sampleRate(sampleRate), m_windowAlpha(windowAlpha), m_oldValue(0), m_newValue(0), m_bufferPosition(0)
    {
        m_windowCoeffs.reserve(m_windowSize);
        // Calculate the window coefficients
        for (int i = 0; i < m_windowSize; i++)
        {
            double x = (double)i / (double)m_windowSize;
            m_windowCoeffs[i] = blackmanHarris(x, m_windowAlpha);
        }
    }
    
    
    static double sinc(double x) {
        if (x == 0) {
            return 1.0;
        } else {
            return std::sin(x) / x;
        }
    }
    
    double blackmanHarris(double x, double alpha) {
        const double a0 = (1 - alpha) / 2;
        const double a1 = 1 / 2;
        const double a2 = alpha / 2;
        return a0 - a1 * std::cos(2 * M_PI * x) + a2 * std::cos(4 * M_PI * x);
    }

    // Set the current parameter value
    void setValue(double value) {
        m_oldValue = m_newValue;
        m_newValue = value;
    }

    // Get the smoothed parameter value for a given time
    double getValue(double t) const {
        double delta = m_newValue - m_oldValue;
        double sincSum = 0.0;
        for (int i = -10; i <= 10; i++) {
            double sincArg = delta / m_tau * (t - i / m_sampleRate);
            sincSum += sinc(sincArg) * m_windowCoeffs[m_bufferPosition + i + m_windowSize/2];
        }
        return m_oldValue + delta / m_tau * sincSum;
    }

    // Get the current buffer position
    int getBufferPosition() const {
        return m_bufferPosition;
    }

    // Increment the buffer position by a given number of samples
    void incrementBufferPosition(int numSamples) {
        m_bufferPosition += numSamples;
        if (m_bufferPosition >= m_windowSize) {
            m_bufferPosition -= m_windowSize;
        }
    }
    
    


private:
    const int m_windowSize = 51;
    double m_tau;
    double m_sampleRate;
    double m_windowAlpha;
    double m_oldValue;
    double m_newValue;
    int m_bufferPosition;
    std::vector<double> m_windowCoeffs;
};












#endif /* SincInterpolator_h */
