/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MidiTestAudioProcessorEditor::MidiTestAudioProcessorEditor (MidiTestAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
    keyboardComponent(p.getKeyboardState(), juce::MidiKeyboardComponent::horizontalKeyboard)
{
    juce::File dir("J:/Samples");

    addAndMakeVisible(filesListBtn);
    filesListBtn.setButtonText("List");
    filesListBtn.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::darkgreen);
    filesListBtn.onClick = [dir]()
    {
        MidiTestAudioProcessor::exploreDir(dir);
    };
    
    addAndMakeVisible(randSoundBtn);
    randSoundBtn.setButtonText("Random");
    randSoundBtn.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::darkgreen);
    randSoundBtn.onClick = [dir]()
    {
        MidiTestAudioProcessor::printRandomSound();
    };


    addAndMakeVisible(keyboardComponent);
    setSize (600, 300);
}

MidiTestAudioProcessorEditor::~MidiTestAudioProcessorEditor()
{
}

//==============================================================================
void MidiTestAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void MidiTestAudioProcessorEditor::resized()
{
    keyboardComponent.setBounds(10, 10, getWidth() - 20, 50);
    filesListBtn.setBounds(100, 100,  65, 50);
    randSoundBtn.setBounds(200, 100, 75, 50);
}
