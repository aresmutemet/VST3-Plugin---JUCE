/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ThePluginAudioProcessor::ThePluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
mPlaying(false)
#endif
{}
ThePluginAudioProcessor::~ThePluginAudioProcessor(){}

const juce::String ThePluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}
bool ThePluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}
bool ThePluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}
bool ThePluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}
double ThePluginAudioProcessor::getTailLengthSeconds() const{return 0.0;}
int ThePluginAudioProcessor::getNumPrograms(){return 1;}
int ThePluginAudioProcessor::getCurrentProgram(){return 0;}
void ThePluginAudioProcessor::setCurrentProgram (int index)
{
}
const juce::String ThePluginAudioProcessor::getProgramName (int index)
{
    return {};
}
void ThePluginAudioProcessor::changeProgramName (int index, const juce::String& newName){}

void ThePluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    Envelope = ADSR(sampleRate);
    SineOscillator = SinOsc(sampleRate);
    SawOscillator = SawOsc(sampleRate);
    lowPassFilter.sampleRate = sampleRate;
    lowPassFilter.reset();
    highPassFilter.sampleRate = sampleRate;
    highPassFilter.reset();
    mSmoothFrequency = 0.0;
}
void ThePluginAudioProcessor::releaseResources(){}
#ifndef JucePlugin_PreferredChannelConfigurations
bool ThePluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif
    return true;
  #endif
}
#endif


void ThePluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    auto* left = buffer.getWritePointer(0);
    auto* right = buffer.getWritePointer(1);
    
    for (const juce::MidiMessageMetadata messages : midiMessages)
        {
            lowPassFilter.setCoefficients(mCuttOffFrequencyParameter, mQParameter);
            highPassFilter.setCoefficients(mCuttOffFrequencyParameter, mQParameter);
            
            const juce::MidiMessage msg = messages.getMessage();
            if (msg.isNoteOn())
            {
                if(adsrParametersNeedUpdate == true)
                {
                    Envelope.setParameters(mAttackParameter, mDecayParameter, mSustainParameter, mReleaseParameter);
                    adsrParametersNeedUpdate = false;
                }
                if(!mPlaying)
                    Envelope.start();
                    SineOscillator.reset();
                    mPlaying = true;
                    mNote = msg.getNoteNumber();
            }
            else if (msg.isNoteOff())
            {
                if (msg.getNoteNumber() == mNote)
                {
                    Envelope.release();
                    mPlaying = false;
                }
            }
        }
        midiMessages.clear();
    
    mMidiFrequency = 0.9 * juce::MidiMessage::getMidiNoteInHertz(mNote) + (1.0 - 0.9) * mSmoothFrequency;
    mSmoothFrequency = mMidiFrequency;
    
    for (auto sample = 0; sample < buffer.getNumSamples(); sample++)
    {
        float sineSignal = SineOscillator.process(mMidiFrequency, juce::Decibels::decibelsToGain(mSineOscGainParameter)) * (1.0 - mMixParameter);
        float sawSignal = SawOscillator.process(mMidiFrequency, juce::Decibels::decibelsToGain(mSawOscGainParameter)) * mMixParameter;
        float adsrSignal = (sineSignal+sawSignal) * Envelope.process();
        float completedSignal;
        switch (filterType)
        {
            case ChooseFilter:
                completedSignal = adsrSignal;
                break;
            case NoFilter:
                completedSignal = adsrSignal;
                break;
                
            case LowPass:
                completedSignal = lowPassFilter.process(adsrSignal);
                break;
                
            case HighPass:
                completedSignal = highPassFilter.process(adsrSignal);
                break;
        }
        
        float gainSignal = completedSignal * juce::Decibels::decibelsToGain(mMakeupGainParameter);
        output = gainSignal;
        left[sample] = output;
        right[sample] = output;
        
    }
}



bool ThePluginAudioProcessor::hasEditor() const{return true;}
juce::AudioProcessorEditor* ThePluginAudioProcessor::createEditor()
{
    return new ThePluginAudioProcessorEditor (*this);
}
void ThePluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData){}
void ThePluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes){}
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ThePluginAudioProcessor();
}
