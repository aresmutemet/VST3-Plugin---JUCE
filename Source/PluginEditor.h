/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class ThePluginAudioProcessorEditor  : public juce::AudioProcessorEditor,
                    public juce::Slider::Listener,
private juce::ComboBox::Listener,
private juce::Timer
{
public:
    ThePluginAudioProcessorEditor (ThePluginAudioProcessor&);
    ~ThePluginAudioProcessorEditor() override;

    //==============================================================================
    void timerCallback() override;
    void paint (juce::Graphics&) override;
    void resized() override;
    

    void sliderValueChanged(juce::Slider* slider)override;
    void comboBoxChanged(juce::ComboBox* comboBox)override;
private:
    
    
    juce::Slider mAttackSlider;
    juce::Slider mDecaySlider;
    juce::Slider mSustainSlider;
    juce::Slider mReleaseSlider;
    juce::Slider mSawOscGainSlider;
    juce::Slider mSineOscGainSlider;
    juce::Slider mMixSlider;
    juce::Slider mMakeupGainSlider;
    
    juce::Slider mCuttOffFrequencySlider;
    juce::Slider mQSlider;
    
    
    juce::Label mMakeupGainLabel;
    juce::Label mAttackLabel;
    juce::Label mDecayLabel;
    juce::Label mSustainLabel;
    juce::Label mReleaseLabel;
    juce::Label mSawOscGainLabel;
    juce::Label mSineOscGainLabel;
    juce::Label mMixLabel;
    
    juce::Label mCuttOffFrequencyLabel;
    juce::Label mQLabel;
    
    juce::ComboBox filterCombo;
    
    ThePluginAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ThePluginAudioProcessorEditor)
};
