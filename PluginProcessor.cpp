/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MidiTestAudioProcessor::MidiTestAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    formatManager.registerBasicFormats();
    keyboardState.addListener(this);
    initialiseSynth();
}

MidiTestAudioProcessor::~MidiTestAudioProcessor()
{
}

void  MidiTestAudioProcessor::handleIncomingMidiMessage(juce::MidiInput* source, const juce::MidiMessage& message)
{
    DBG("plugin processor 36");
    //keyboardState.processNextMidiEvent(message);
}

void MidiTestAudioProcessor::handleNoteOn(juce::MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity)
{

    mySynth.noteOn(midiChannel, midiNoteNumber, velocity);
    DBG(velocity);

}

void MidiTestAudioProcessor::handleNoteOff(juce::MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity)
{
    mySynth.noteOff(midiChannel, midiNoteNumber, velocity, true);
}

std::unique_ptr<juce::AudioFormatReader> MidiTestAudioProcessor::loadFile(juce::File& file)
{
    //auto file = juce::File("D:/usb_connect.wav");

    std::unique_ptr<juce::AudioFormatReader> reader(formatManager.createReaderFor(file));

    return reader;
}

void MidiTestAudioProcessor::initialiseSynth() {
    mySynth.clearVoices();
    mySynth.clearSounds();

    for (int i = 0; i < 4; i++) {
        mySynth.addVoice(new MySamplerVoice());
    }

    std::unique_ptr<juce::AudioFormatReader> reader = loadFile(juce::File("J:/Samples/carhorn.wav"));

    std::unique_ptr<juce::AudioFormatReader> reader1 = loadFile(juce::File("J:/Samples/carhorn.wav"));

    juce::BigInteger range;
    range.setBit(72);

    juce::BigInteger range1;
    range1.setBit(73);

    mySynth.addSound(new juce::SamplerSound(
        "sample",
        *reader,
        range,
        72,
        0.1,
        0.1,
        10.0,
        0.0f,
        1.5f
    ));

    mySynth.addSound(new juce::SamplerSound(
        "sample",
        *reader1,
        range,
        72,
        0.1,
        0.1,
        10.0,
        0.5f,
        1.0f
    ));
    
    mySynth.addSound(new juce::SamplerSound(
        "sample",
        *reader1,
        range1,
        73,
        0.1,
        0.1,
        10.0,
        1.0f,
        1.0f
    ));
}

//==============================================================================
const juce::String MidiTestAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MidiTestAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MidiTestAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MidiTestAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MidiTestAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MidiTestAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MidiTestAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MidiTestAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String MidiTestAudioProcessor::getProgramName (int index)
{
    return {};
}

void MidiTestAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void MidiTestAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    lastSampleRate = sampleRate;
    mySynth.setCurrentPlaybackSampleRate(lastSampleRate);
}

void MidiTestAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MidiTestAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void MidiTestAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    buffer.clear();
    mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

}

//==============================================================================
bool MidiTestAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* MidiTestAudioProcessor::createEditor()
{
    return new MidiTestAudioProcessorEditor (*this);
}

//==============================================================================
void MidiTestAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MidiTestAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MidiTestAudioProcessor();
}

void MidiTestAudioProcessor::exploreDir(const juce::File& directory)
{
    if (directory.isDirectory())
    {
        juce::Array<juce::File> files;
        directory.findChildFiles(files, juce::File::findFiles | juce::File::findDirectories, true);

        for (const auto& file : files)
        {
            if (file.isDirectory())
            {
                DBG("Directory: " << file.getFileName());
                //exploreDir(file);  // Рекурсивный вызов для обхода подпапок
            }
            else
            {
                DBG("  File: " << file.getFullPathName());
                soundPaths.add(file.getFullPathName());
            }
        }

    }
}

void MidiTestAudioProcessor::printRandomSound()
{
    if (soundPaths.size() > 0)
    {
        std::srand(std::time(nullptr)); // Инициализация генератора случайных чисел
        int randomIndex = std::rand() % soundPaths.size(); // Генерация случайного индекса
        juce::String randomSound = soundPaths[randomIndex];
        DBG("Random sound: " << randomSound);
    }
    else
    {
        DBG("No sound files found!");
    }
}

juce::StringArray MidiTestAudioProcessor::soundPaths;