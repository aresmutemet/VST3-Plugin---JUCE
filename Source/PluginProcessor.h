/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ADSR.h"
#include "SinOsc.h"
#include "SawOsc.h"
#include "LPFilter.h"
#include "HPFilter.h"

//==============================================================================
/**
*/
class ThePluginAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    
    
    ADSR Envelope;
    SinOsc SineOscillator;
    SawOsc SawOscillator;
    LPFilter lowPassFilter;
    HPFilter highPassFilter;
    
    float output;
    bool mPlaying;
    int mNote;
    double mSmoothFrequency;
    float mMidiFrequency;
    
    float mSawOscGainParameter;
    float mSineOscGainParameter;
    float mMixParameter;
    float mMakeupGainParameter;
    
    float mAttackParameter=0.01;
    float mDecayParameter=0.5;
    float mSustainParameter=0.3;
    float mReleaseParameter =0.3;
    
    float mCuttOffFrequencyParameter;
    float mQParameter;
    
    enum FilterType
        {
            ChooseFilter = 1,
            NoFilter = 2,
            LowPass = 3,
            HighPass = 4,
            
        };

        FilterType filterType;
    bool adsrParametersNeedUpdate = false;
    //==============================================================================
    ThePluginAudioProcessor();
    ~ThePluginAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
   
    
private:
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ThePluginAudioProcessor)
};
