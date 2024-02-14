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
class MidiTestAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    MidiTestAudioProcessorEditor (MidiTestAudioProcessor&);
    ~MidiTestAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MidiTestAudioProcessor& audioProcessor;
    juce::MidiKeyboardComponent keyboardComponent;
    juce::TextButton filesListBtn;
    juce::TextButton randSoundBtn;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiTestAudioProcessorEditor)
};
