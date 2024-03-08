/*
  ==============================================================================

    SawOscillator.h
    Created: 13 Jun 2023 9:38:57am
    Author:  Areş Mutemet

  ==============================================================================
*/

#pragma once

class SawOsc {
public:
    SawOsc (float sampleRate = 44100):mSampleRate(sampleRate){}
    
    float polyBlep(float t, float dt)
    {
        if (t < dt)
        {
            t /= dt;
            return t + t - t * t - 1.0;
        }
        else if (t > 1.0 - dt)
        {
            t = (t - 1.0) / dt;
            return t * t + t + t + 1.0;
        }
        else return 0;
    }
    
    float process(float freq, float amplitude)
    {
        float result = amplitude * (2 * mPhase - 1) - polyBlep(mPhase, mIncr);
        if (freq != mFreq)
        {
            mIncr = freq / mSampleRate;
            freq = mFreq;
        }
        mPhase = fmod(mPhase + mIncr, 1.0);
        return result;
    }
    
    
    
private:
    float mPhase{0};
    float mFreq{0};
    float mSampleRate{0};
    float mIncr{0};
};
