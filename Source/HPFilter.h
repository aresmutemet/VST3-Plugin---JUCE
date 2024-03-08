/*
  ==============================================================================

    HighPassFilter.h
    Created: 13 Jun 2023 9:40:03am
    Author:  Areş Mutemet

  ==============================================================================
*/

#pragma once

class HPFilter
{
public:
    float sampleRate;
    
    void setCoefficients(float cutoffFrequency, float Q)
    {
        g = std::tan(PI * cutoffFrequency / sampleRate);
        k = 1.0f / Q;
        a1 = 1.0f / (1.0f + g * (g + k));
        a2 = g * a1;
        a3 = g * a2;
        a4 = k * a1;
    }

    void reset()
    {
        g = 0.0f;
        k = 0.0f;
        a1 = 0.0f;
        a2 = 0.0f;
        a3 = 0.0f;
        a4 = 0.0f;

        s1 = 0.0f;
        s2 = 0.0f;
    }

    float process(float x)
    {
        float v3 = x - s2;
        float v1 = a1 * s1 + a2 * v3;
        float v2 = s2 + a2 * s1 + a3 * v3;
        s1 = 2.0f * v1 - s1;
        s2 = 2.0f * v2 - s2;
        return x - a4 * v1 - v2;
    }

private:
    const float PI = 3.1415926535897932f;
    float g, k, a1, a2, a3, a4;
    float s1, s2;
};



