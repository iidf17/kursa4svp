/*
  ==============================================================================

    MySynthesiser.h
    Created: 4 Feb 2024 4:51:45pm
    Author:  chere

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class MySynthesiser : public juce::Synthesiser {
public:
    MySynthesiser();
    ~MySynthesiser();

    void noteOn(int midiChannel, int midiNoteNumber, float velocity) override;

private:
    bool shouldStealNotes = true;
};