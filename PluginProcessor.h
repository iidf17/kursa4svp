/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "MySynthesiser.h"

#include <JuceHeader.h>

//==============================================================================
/**
*/
class MidiTestAudioProcessor  : public juce::AudioProcessor,
    public juce::MidiKeyboardStateListener
{
public:
    //==============================================================================
    MidiTestAudioProcessor();
    ~MidiTestAudioProcessor() override;

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

    //==============================================================================
    juce::MidiKeyboardState& getKeyboardState() { return keyboardState; }
    void initialiseSynth();

    static void exploreDir(const juce::File& directory);
    static void printRandomSound();

    void handleNoteOff(juce::MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) override;
    void handleNoteOn(juce::MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) override;
    void handleIncomingMidiMessage(juce::MidiInput* source, const juce::MidiMessage& message);

    std::unique_ptr<juce::AudioFormatReader> loadFile(juce::File& file);
private:
    juce::MidiKeyboardState keyboardState;
    juce::Synthesiser mySynth;

    static juce::StringArray soundPaths;
    //MySynthesiser mySynthesiser;

    juce::AudioFormatManager formatManager;

    double lastSampleRate;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiTestAudioProcessor)
};

class MySamplerVoice : public juce::SamplerVoice {
public:
    MySamplerVoice() {};
    ~MySamplerVoice() {};

    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* s, int currentPitchWheelPosition) override
    {
        juce::SamplerVoice::startNote(midiNoteNumber, velocity, s, currentPitchWheelPosition);

    }
};
