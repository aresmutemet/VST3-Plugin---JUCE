/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ThePluginAudioProcessorEditor::ThePluginAudioProcessorEditor (ThePluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    
    
    audioProcessor.filterType = ThePluginAudioProcessor::ChooseFilter;
    
    mMixSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    mMixSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 1, 1);
    mMixSlider.setRange(0.f, 1.0f, 0.01f);
    mMixSlider.setValue(0.5f);
    mMixSlider.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::limegreen.darker());
    mMixSlider.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::limegreen.brighter());
    mMixSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::limegreen);
    mMixSlider.setDoubleClickReturnValue(true, 0.5f);
    mMixSlider.addListener(this);
    mMixLabel.setText ("Sine<--Mix Level-->Sawtooth", juce::dontSendNotification);
    mMixLabel.setFont(20.0f);
    mMixLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::burlywood);
    
    mMakeupGainSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    mMakeupGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    mMakeupGainSlider.setRange(-24.f, 24.f, 1.f);
    mMakeupGainSlider.setValue(0.f);
    mMakeupGainSlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::greenyellow.brighter());
    mMakeupGainSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::limegreen);
    mMakeupGainSlider.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::grey.brighter());
    mMakeupGainSlider.setDoubleClickReturnValue(true, 0.f);
    mMakeupGainSlider.addListener(this);
    mMakeupGainLabel.setText ("MakeUp Gain(dB)", juce::dontSendNotification);
    
    mSineOscGainSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    mSineOscGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    mSineOscGainSlider.setRange(-12.f, 12.f, 1.f);
    mSineOscGainSlider.setValue(0.f);
    mSineOscGainSlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::greenyellow.brighter());
    mSineOscGainSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::limegreen);
    mSineOscGainSlider.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::grey.brighter());
    mSineOscGainSlider.setDoubleClickReturnValue(true, 0.f);
    mSineOscGainSlider.addListener(this);
    mSineOscGainLabel.setText ("Sine Gain(dB)", juce::dontSendNotification);

    mSawOscGainSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    mSawOscGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    mSawOscGainSlider.setRange(-12.f, 12.f, 1.f);
    mSawOscGainSlider.setValue(0.f);
    mSawOscGainSlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::greenyellow.brighter());
    mSawOscGainSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::limegreen);
    mSawOscGainSlider.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::grey.brighter());
    mSawOscGainSlider.setDoubleClickReturnValue(true, 0.f);
    mSawOscGainSlider.addListener(this);
    mSawOscGainLabel.setText ("Sawtooth Gain(dB)", juce::dontSendNotification);
    
    mAttackSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    mAttackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    mAttackSlider.setRange(0.01f, 1.0f, 0.01f);
    mAttackSlider.setValue(0.2f);
    mAttackSlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::red.brighter());
    mAttackSlider.setDoubleClickReturnValue(true, 0.01f);
    mAttackSlider.addListener(this);
    mAttackLabel.setText ("Attack(ms)", juce::dontSendNotification);
    
    mDecaySlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    mDecaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    mDecaySlider.setRange(0.01f, 2.0f, 0.01f);
    mDecaySlider.setValue(0.4f);
    mDecaySlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::blue.brighter());
    mDecaySlider.setDoubleClickReturnValue(true, 0.5f);
    mDecaySlider.addListener(this);
    mDecayLabel.setText ("Decay(ms)", juce::dontSendNotification);
    
    mSustainSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    mSustainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    mSustainSlider.setRange(0.0f, 1.0f, 0.01f);
    mSustainSlider.setValue(0.3f);
    mSustainSlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::purple.brighter());
    mSustainSlider.setDoubleClickReturnValue(true, 0.3f);
    mSustainSlider.addListener(this);
    mSustainLabel.setText ("Sustain(ms)", juce::dontSendNotification);
    
    mReleaseSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    mReleaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    mReleaseSlider.setRange(0.01f, 2.0f, 0.01f);
    mReleaseSlider.setValue(0.3f);
    mReleaseSlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::yellow.brighter());
    mReleaseSlider.setDoubleClickReturnValue(true, 0.3f);
    mReleaseSlider.addListener(this);
    mReleaseLabel.setText ("Release(ms)", juce::dontSendNotification);
    
    
    mCuttOffFrequencySlider.setSliderStyle(juce::Slider::LinearBarVertical);
    mCuttOffFrequencySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    mCuttOffFrequencySlider.setRange(20.0f, 20000.0f, 1.f);
    mCuttOffFrequencySlider.setValue(3200.0f);
    
    mCuttOffFrequencySlider.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::limegreen);
    mCuttOffFrequencySlider.setDoubleClickReturnValue(true, 5000.0f);
    mCuttOffFrequencySlider.addListener(this);
    mCuttOffFrequencyLabel.setText ("Cuttoff Frequency      (Hz)", juce::dontSendNotification);
    
    mQSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    mQSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    mQSlider.setRange(1.0f, 10.f, 0.1f);
    mQSlider.setValue(4.0f);
    mQSlider.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::limegreen);
    mQSlider.setDoubleClickReturnValue(true, 2.0f);
    mQSlider.addListener(this);
    mQLabel.setText ("Q Factor", juce::dontSendNotification);
    
    filterCombo.addItem("Choose Filter", 1);
    filterCombo.addItem("No Filter", 2);
    filterCombo.addItem("LowPass", 3);
    filterCombo.addItem("HighPass", 4);
    filterCombo.setSelectedId(1);
    filterCombo.setColour(juce::ComboBox::ColourIds::backgroundColourId, juce::Colours::gold);
    filterCombo.setColour(juce::ComboBox::ColourIds::textColourId, juce::Colours::black);
    filterCombo.addListener(this);
    
    startTimerHz(30);
    
    
    addAndMakeVisible(mMixSlider);
    addAndMakeVisible(mMixLabel);
    
    addAndMakeVisible(mMakeupGainSlider);
    addAndMakeVisible (mMakeupGainLabel);
    
    addAndMakeVisible(mSineOscGainSlider);
    addAndMakeVisible (mSineOscGainLabel);
    addAndMakeVisible(mSawOscGainSlider);
    addAndMakeVisible (mSawOscGainLabel);
    
    addAndMakeVisible(mAttackLabel);
    addAndMakeVisible (mAttackSlider);
    addAndMakeVisible(mDecayLabel);
    addAndMakeVisible (mDecaySlider);
    addAndMakeVisible(mSustainLabel);
    addAndMakeVisible (mSustainSlider);
    addAndMakeVisible(mReleaseLabel);
    addAndMakeVisible (mReleaseSlider);
    
    addAndMakeVisible(mCuttOffFrequencySlider);
    addAndMakeVisible(mCuttOffFrequencyLabel);
    addAndMakeVisible(mQLabel);
    addAndMakeVisible(mQSlider);
    
    addAndMakeVisible(filterCombo);
    

    
    
//    setResizable(true, true);
//    setResizeLimits(600, 250, 1200, 600);
//    getConstrainer()->setFixedAspectRatio(2.0);
    setSize (1000, 600);
}

ThePluginAudioProcessorEditor::~ThePluginAudioProcessorEditor()
{
}

//==============================================================================
void ThePluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::darkgreen.darker());
    g.setColour(juce::Colours::yellowgreen.brighter());
    g.setFont(40.0f);
    g.drawFittedText("The Oscillator Plugin", getLocalBounds(), juce::Justification::centredTop, 1);
    
    g.setColour(juce::Colours::green);
    g.fillRect(juce::Rectangle<float>(getWidth() - 20, getHeight(), 1000, -audioProcessor.output * getHeight()*3));
    
}

void ThePluginAudioProcessorEditor::timerCallback()
{
    repaint();
}

void ThePluginAudioProcessorEditor::resized()
{
 
    auto xCenter = getWidth()/2;
    auto yCenter = getHeight()/2 + 70;
    
    
    
    mMakeupGainSlider.setBounds(xCenter - 70, yCenter - 180, 150, 150);
    mMakeupGainLabel.setBounds(xCenter - 50, yCenter - 200, 100, 20);
    
    mSineOscGainSlider.setBounds(xCenter - 200, yCenter -260, 120, 120);
    mSineOscGainLabel.setBounds(xCenter - 190, yCenter - 280 , 100, 20);
    mSawOscGainSlider.setBounds(xCenter + 80, yCenter - 260, 120, 120);
    mSawOscGainLabel.setBounds(xCenter + 90, yCenter - 280, 100, 20);
    
    mMixSlider.setBounds(xCenter-250, yCenter - 40 , 500, 100);
    mMixLabel.setBounds(xCenter - 80, yCenter + 10, 200, 60);
    
    mAttackSlider.setBounds(xCenter - 230, yCenter + 70, 100, 100);
    mAttackLabel.setBounds(xCenter - 220, yCenter + 180, 80, 20);
    mDecaySlider.setBounds(xCenter - 110, yCenter + 70, 100, 100);
    mDecayLabel.setBounds(xCenter - 90, yCenter + 180, 80, 20);
    mSustainSlider.setBounds(xCenter + 10, yCenter + 70, 100, 100);
    mSustainLabel.setBounds(xCenter + 20, yCenter + 180, 80, 20);
    mReleaseSlider.setBounds(xCenter + 130, yCenter + 70, 100, 100);
    mReleaseLabel.setBounds(xCenter + 140, yCenter + 180, 80, 20);
    
    mCuttOffFrequencySlider.setBounds(xCenter -500, yCenter - 300, 100, 530);
    mQSlider.setBounds(xCenter-400, yCenter -300, 100, 530);
    filterCombo.setBounds(xCenter-500, yCenter-370, 200, 70);
    mCuttOffFrequencyLabel.setBounds(xCenter-500, yCenter - 30, 100, 40);
    
  
}
void ThePluginAudioProcessorEditor::sliderValueChanged(juce::Slider *slider)
{
    if (slider == &mMakeupGainSlider) {
        
        audioProcessor.mMakeupGainParameter = mMakeupGainSlider.getValue();
        
    }else if (slider == &mSineOscGainSlider){
        
        audioProcessor.mSineOscGainParameter = mSineOscGainSlider.getValue();
        
    }else if (slider == &mSawOscGainSlider){
        
        audioProcessor.mSawOscGainParameter = mSawOscGainSlider.getValue();
        
    }else if (slider == &mAttackSlider){
        
        audioProcessor.mAttackParameter = mAttackSlider.getValue();
        audioProcessor.adsrParametersNeedUpdate = true;
        
    }else if (slider == &mDecaySlider){
        
        audioProcessor.mDecayParameter = mDecaySlider.getValue();
        audioProcessor.adsrParametersNeedUpdate = true;
        
    }else if (slider == &mSustainSlider){
        
        audioProcessor.mSustainParameter = mSustainSlider.getValue();
        audioProcessor.adsrParametersNeedUpdate = true;
        
    }else if (slider == &mReleaseSlider){
        
        audioProcessor.mReleaseParameter = mReleaseSlider.getValue();
        audioProcessor.adsrParametersNeedUpdate = true;
        
    }else if (slider == &mMixSlider){
        audioProcessor.mMixParameter = mMixSlider.getValue();
    }else if (slider == &mCuttOffFrequencySlider){
        audioProcessor.mCuttOffFrequencyParameter = mCuttOffFrequencySlider.getValue();
    }else if (slider == &mQSlider){
        audioProcessor.mQParameter = mQSlider.getValue();
    }
}
void ThePluginAudioProcessorEditor::comboBoxChanged(juce::ComboBox* comboBox)
{
    if (comboBox == &filterCombo)
    {
        audioProcessor.filterType = static_cast<ThePluginAudioProcessor::FilterType>(comboBox->getSelectedId());

    }
}




