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

struct TimeSeriesDisplay;

class AirWinJuceToyAudioProcessorEditor : public juce::AudioProcessorEditor, juce::Slider::Listener
{
  public:
    AirWinJuceToyAudioProcessorEditor(AirWinJuceToyAudioProcessor &);
    ~AirWinJuceToyAudioProcessorEditor();

    //==============================================================================
    void paint(juce::Graphics &) override;
    void resized() override;

    std::array<std::unique_ptr<juce::Slider>, AirWinJuceToyAudioProcessor::n_params> sliders;
    std::array<std::unique_ptr<juce::Label>, AirWinJuceToyAudioProcessor::n_params> labels;
    std::unique_ptr<TimeSeriesDisplay> tsdisplay;

    void sliderValueChanged(juce::Slider *) override;
    void sliderDragStarted(juce::Slider *) override;
    void sliderDragEnded(juce::Slider *) override;
    void sliderDragInternal(juce::Slider *, bool started);

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
