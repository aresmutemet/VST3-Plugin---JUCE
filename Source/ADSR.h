/*
  ==============================================================================

    Envelope.h
    Created: 13 Jun 2023 9:39:33am
    Author:  Areş Mutemet

  ==============================================================================
*/

#pragma once

class ADSR {
public:
    ADSR(float sampleRate = 44100): mSampleRate(sampleRate){}
    
    void setParameters(float attackTime, float decayTime, float sustainTime, float releaseTime )
    {
        mSustain  = sustainTime;
        mAttack  = 1 / (attackTime * mSampleRate);
        mDacay   = (1 - sustainTime) / (decayTime * mSampleRate);
        mRelease = (1 - sustainTime) / (releaseTime * mSampleRate);
        mValue = 0;
        mState = 4; // 0 attack, 1 decay, 2 sustain, 3 release, 4 finished
    }
    
    void start()
    {
        mValue = 0;
        mState = 0;
    }
    void release()
    {
        mState = 3;
    }
    
    double process()
    {
        switch (mState)
        {
            case 0:
                mValue += mAttack;
                if(mValue >= 1)
                {
                    mState = 1;
                }
                break;
            case 1:
                mValue -= mDacay;
                if(mValue <= mSustain)
                {
                    mState = 2;
                }
                break;
            case 2:
                break;
            case 3:
                mValue -= mRelease;
                if(mValue <= 0)
                {
                    mState = 4;
                }
                break;
        }
        return mValue;
    }
    
private:
    float  mSampleRate;
    float  mAttack;
    float  mDacay;
    float  mSustain;
    float  mRelease;
    
    float mValue;
    int mState;
};

