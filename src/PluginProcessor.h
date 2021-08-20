/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <set>
#include "LockFreeQueue.h"

class AirWinJuceToyAudioProcessor;

class AirWinJuceToyAudioProcessor : public juce::AudioProcessor,
                                    public juce::AudioProcessorParameter::Listener
{
  public:
    //==============================================================================
    AirWinJuceToyAudioProcessor();
    ~AirWinJuceToyAudioProcessor();

    /*
     * I use a simple linear data structure on both the UI and Audio side for my
     * 3 parameters, indexed by this enum
     */
    enum Parameters
    {
        GAIN = 0,
        CUTOFF,
        RESONANCE
    };
    static constexpr int n_params = RESONANCE + 1;

    std::array<juce::AudioParameterFloat *, n_params> params;

    struct UIToAudioMessage
    {
        enum What
        {
            NEW_VALUE,
            BEGIN_EDIT,
            END_EDIT
        } what{NEW_VALUE};
        Parameters which;
        float newValue{0.f};
    };
    struct AudioToUIMessage
    {
        enum What
        {
            NEW_VALUE,
            RMS
        } what{NEW_VALUE};
        Parameters which;
        float newValue{0.f};
    };
    LockFreeQueue<UIToAudioMessage> uiToAudio;
    LockFreeQueue<AudioToUIMessage> audioToUI;

    float rmsIn{0.f};
    int nrms{0};

    void parameterValueChanged(int parameterIndex, float newValue) override;
    void parameterGestureChanged(int parameterIndex, bool starting) override;

    //==============================================================================
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported(const BusesLayout &layouts) const override;

    void processBlock(juce::AudioBuffer<float> &, juce::MidiBuffer &) override;

    //==============================================================================
    juce::AudioProcessorEditor *createEditor() override;
    bool hasEditor() const override { return true; }

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }

    //==============================================================================
    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int index) override {}
    const juce::String getProgramName(int index) override { return {}; }
    void changeProgramName(int index, const juce::String &newName) override {}

    //==============================================================================
    void getStateInformation(juce::MemoryBlock &destData) override;
    void setStateInformation(const void *data, int sizeInBytes) override;

    float priorCutoff{-1.0};
    float b[3], a[3];
    float yN[3][2], xN[3][2];

  private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AirWinJuceToyAudioProcessor)
};
