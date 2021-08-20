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
    /*
     * Create and add my parameter objects
     */
    addParameter(params[GAIN] = new juce::AudioParameterFloat(
                     "gain",     // the ID - this has to be stable across versions
                     "Gain",     // how you show it to the DAW
                     {0.f, 1.f}, // min and max
                     1));        // and default
    addParameter(params[CUTOFF] =
                     new juce::AudioParameterFloat("lpf-cutoff", "LPF Cutoff", {1.f, 127.f}, 69));
    addParameter(params[RESONANCE] = new juce::AudioParameterFloat("lpf-resonance", "LPF Resonance",
                                                                   {0.f, 1.f}, 69));

    for (int i = 0; i < n_params; ++i)
    {
        params[i]->addListener(this);
    }

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 2; ++j)
        {
            yN[i][j] = 0.f;
            xN[i][j] = 0.f;
        }
}

AirWinJuceToyAudioProcessor::~AirWinJuceToyAudioProcessor() {}

//==============================================================================
const String AirWinJuceToyAudioProcessor::getName() const { return JucePlugin_Name; }

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
    /*
     * Handle inbound messages from the UI thread
     */
    UIToAudioMessage uim;
    while (uiToAudio.pop(uim))
    {
        switch (uim.what)
        {
        case UIToAudioMessage::NEW_VALUE:
            params[uim.which]->setValueNotifyingHost(
                params[uim.which]->convertTo0to1(uim.newValue));
            break;

        case UIToAudioMessage::BEGIN_EDIT:
            params[uim.which]->beginChangeGesture();
            break;

        case UIToAudioMessage::END_EDIT:
            params[uim.which]->endChangeGesture();
            break;
        }
    }

    auto mainOutput = getBusBuffer(buffer, false, 0);
    auto mainInput = getBusBuffer(buffer, true, 0);

    /*
     * Of course good DSP would smooth these parameters and stuff
     */
    auto gainf = params[GAIN]->get();

    auto freq = pow(2.0, (params[CUTOFF]->get() - 69) / 12.0) * 440;

    auto omega = 2.0 * M_PI * freq / getSampleRate();
    auto alpha = sin(omega) / std::max(0.01f, params[RESONANCE]->get());
    auto cosw = cos(omega);

    auto a0 = 1 + alpha;
    b[0] = (1.0 - cosw) / 2.0 / a0;
    b[1] = (1.0 - cosw) / a0;
    b[2] = b[0];
    a[0] = 1;
    a[1] = (-2 * cosw) / a0;
    a[2] = (1 - alpha) / a0;

    for (int i = 0; i < buffer.getNumSamples(); ++i)
    {
        auto outL = mainOutput.getWritePointer(0, i);
        auto outR = mainOutput.getWritePointer(1, i);
        auto inL = mainInput.getReadPointer(0, i);
        auto inR = mainInput.getReadPointer(1, i);

        for (int c = 0; c < 2; ++c)
        {
            xN[2][c] = xN[1][c];
            xN[1][c] = xN[0][c];
            xN[0][c] = (c == 0 ? *inL : *inR);

            yN[2][c] = yN[1][c];
            yN[1][c] = yN[0][c];
            yN[0][c] = b[0] * xN[0][c] + b[1] * xN[1][c] + b[2] * xN[2][c] - a[1] * yN[1][c] -
                       a[2] * yN[2][c];
        }

        *outL = yN[0][0] * gainf;
        *outR = yN[0][1] * gainf;

        rmsIn += *inL * *inL + *inR * *inR;
        nrms++;
    }

    if (nrms > 512)
    {
        AudioToUIMessage msg;
        msg.what = AudioToUIMessage::RMS;
        msg.newValue = sqrt(rmsIn / nrms / 2);
        audioToUI.push(msg);
        nrms = 0;
        rmsIn = 0.f;
    }
}

AudioProcessorEditor *AirWinJuceToyAudioProcessor::createEditor()
{
    return new AirWinJuceToyAudioProcessorEditor(*this);
}

//==============================================================================
void AirWinJuceToyAudioProcessor::getStateInformation(MemoryBlock &destData) {}

void AirWinJuceToyAudioProcessor::setStateInformation(const void *data, int sizeInBytes) {}

void AirWinJuceToyAudioProcessor::parameterValueChanged(int parameterIndex, float newValue)
{
    AudioToUIMessage msg;
    msg.what = AudioToUIMessage::NEW_VALUE;
    msg.which = (AirWinJuceToyAudioProcessor::Parameters)parameterIndex;
    msg.newValue = params[parameterIndex]->convertFrom0to1(newValue);
    audioToUI.push(msg);
}
void AirWinJuceToyAudioProcessor::parameterGestureChanged(int parameterIndex, bool starting) {}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor *JUCE_CALLTYPE createPluginFilter() { return new AirWinJuceToyAudioProcessor(); }
