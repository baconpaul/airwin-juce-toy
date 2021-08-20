/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

using namespace juce;

//==============================================================================
AirWinJuceToyAudioProcessor::AirWinJuceToyAudioProcessor()
    : AudioProcessor(BusesProperties()
                         .withOutput("Output", AudioChannelSet::stereo(), true)
                         .withInput("Input", AudioChannelSet::stereo(), true))
{
}

AirWinJuceToyAudioProcessor::~AirWinJuceToyAudioProcessor() {}

//==============================================================================
const String AirWinJuceToyAudioProcessor::getName() const { return JucePlugin_Name; }

bool AirWinJuceToyAudioProcessor::acceptsMidi() const { return true; }

bool AirWinJuceToyAudioProcessor::producesMidi() const { return false; }

bool AirWinJuceToyAudioProcessor::isMidiEffect() const { return false; }

double AirWinJuceToyAudioProcessor::getTailLengthSeconds() const { return 0.0; }

int AirWinJuceToyAudioProcessor::getNumPrograms()
{
    return 1; // NB: some hosts don't cope very well if you tell them there are 0 programs,
              // so this should be at least 1, even if you're not really implementing programs.
}

int AirWinJuceToyAudioProcessor::getCurrentProgram() { return 0; }

void AirWinJuceToyAudioProcessor::setCurrentProgram(int index) {}

const String AirWinJuceToyAudioProcessor::getProgramName(int index) { return {}; }

void AirWinJuceToyAudioProcessor::changeProgramName(int index, const String &newName) {}

//==============================================================================
void AirWinJuceToyAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {}

void AirWinJuceToyAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool AirWinJuceToyAudioProcessor::isBusesLayoutSupported(const BusesLayout &layouts) const
{
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono() &&
        layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;

    return true;
}

void AirWinJuceToyAudioProcessor::processBlock(AudioBuffer<float> &buffer, MidiBuffer &midiMessages)
{
}

//==============================================================================
bool AirWinJuceToyAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor *AirWinJuceToyAudioProcessor::createEditor()
{
    return new AirWinJuceToyAudioProcessorEditor(*this);
}

//==============================================================================
void AirWinJuceToyAudioProcessor::getStateInformation(MemoryBlock &destData) {}

void AirWinJuceToyAudioProcessor::setStateInformation(const void *data, int sizeInBytes) {}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor *JUCE_CALLTYPE createPluginFilter() { return new AirWinJuceToyAudioProcessor(); }
