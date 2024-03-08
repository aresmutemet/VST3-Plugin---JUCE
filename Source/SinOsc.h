/*
  ==============================================================================

    SineOscillator.h
    Created: 13 Jun 2023 9:37:35am
    Author:  Areş Mutemet

  ==============================================================================
*/

#pragma once

#include <cmath>

class SinOsc {
public:
    SinOsc (float sampleRate = 44100): mSampleRate(sampleRate){}

    float process(float freq, float amplitude)
    {
        float result = amplitude * sin(2.0 * M_PI * freq * mPhase);
        mPhase += freq / mSampleRate;
        if (mPhase >= 1.0) mPhase -= 1.0;
        return result;
    }
    
    void reset() { mPhase = 0; }
    
private:
    float mPhase{0};
    float mSampleRate;
};
