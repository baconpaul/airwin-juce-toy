/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

using namespace juce;

//==============================================================================
AirWinJuceToyAudioProcessorEditor::AirWinJuceToyAudioProcessorEditor(AirWinJuceToyAudioProcessor &p)
    : AudioProcessorEditor(&p), processor(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(784, 742);

    idleTimer = std::make_unique<IdleTimer>(this);
    idleTimer->startTimer(1000 / 30);
}

AirWinJuceToyAudioProcessorEditor::~AirWinJuceToyAudioProcessorEditor() {}

//==============================================================================
void AirWinJuceToyAudioProcessorEditor::paint(Graphics &g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void AirWinJuceToyAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void AirWinJuceToyAudioProcessorEditor::sliderValueChanged(juce::Slider *s) {}

void AirWinJuceToyAudioProcessorEditor::idle() {}
