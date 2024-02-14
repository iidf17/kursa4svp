/*
  ==============================================================================

    MySynthesiser.cpp
    Created: 4 Feb 2024 4:51:45pm
    Author:  chere

  ==============================================================================
*/

#include "MySynthesiser.h"

MySynthesiser::MySynthesiser() 
{

}

MySynthesiser::~MySynthesiser() 
{

}

void MySynthesiser::noteOn(int midiChannel, int midiNoteNumber, float velocity)
{
    for (auto* sound : sounds)
    {
        if (sound->appliesToNote(midiNoteNumber) && sound->appliesToChannel(midiChannel))
        {
            // If hitting a note that's still ringing, stop it first (it could be
            // still playing because of the sustain or sostenuto pedal).
            for (auto* voice : voices)
                if (voice->getCurrentlyPlayingNote() == midiNoteNumber && voice->isPlayingChannel(midiChannel))
                    stopVoice(voice, 1.0f, true);

            startVoice(findFreeVoice(sound, midiChannel, midiNoteNumber, shouldStealNotes),
                sound, midiChannel, midiNoteNumber, velocity);
        }
    }
}