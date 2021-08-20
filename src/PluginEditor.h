/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
 */
class AirWinJuceToyAudioProcessorEditor : public juce::AudioProcessorEditor, juce::Slider::Listener
{
  public:
    AirWinJuceToyAudioProcessorEditor(AirWinJuceToyAudioProcessor &);
    ~AirWinJuceToyAudioProcessorEditor();

    //==============================================================================
    void paint(juce::Graphics &) override;
    void resized() override;

    void sliderValueChanged(juce::Slider *) override;

    struct IdleTimer : juce::Timer
    {
        IdleTimer(AirWinJuceToyAudioProcessorEditor *ed) : ed(ed) {}
        ~IdleTimer() = default;
        void timerCallback() override { ed->idle(); }
        AirWinJuceToyAudioProcessorEditor *ed;
    };
    void idle();

  private:
    std::unique_ptr<IdleTimer> idleTimer;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AirWinJuceToyAudioProcessor &processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AirWinJuceToyAudioProcessorEditor)
};
