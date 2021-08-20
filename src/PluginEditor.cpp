/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "TimeSeriesDisplay.h"

using namespace juce;

//==============================================================================
AirWinJuceToyAudioProcessorEditor::AirWinJuceToyAudioProcessorEditor(AirWinJuceToyAudioProcessor &p)
    : AudioProcessorEditor(&p), processor(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(400, 300);
    setResizable(false, false);

    idleTimer = std::make_unique<IdleTimer>(this);
    idleTimer->startTimer(1000 / 30);

    const char *lab[3] = {"Gain", "Cutoff", "Resonance"};
    for (int p = AirWinJuceToyAudioProcessor::GAIN; p <= AirWinJuceToyAudioProcessor::RESONANCE;
         ++p)
    {
        auto xmg = (getWidth() - 3 * 110) / 2;
        auto xpos = xmg + p * 110;
        auto n = std::make_unique<juce::Slider>(juce::String(lab[p]) + " Slider");
        n->setSliderStyle(juce::Slider::RotaryVerticalDrag);
        n->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
        if (p == AirWinJuceToyAudioProcessor::CUTOFF)
            n->setRange(1.f, 127.f);
        else
            n->setRange(0.f, 1.f);
        n->setValue(processor.params[p]->get(), juce::NotificationType::dontSendNotification);
        n->setBounds(juce::Rectangle<int>(xpos, 170, 100, 120));
        n->addListener(this);
        addAndMakeVisible(*n);

        auto l = std::make_unique<juce::Label>(juce::String(lab[p]) + " Label", lab[p]);
        l->setBounds(xpos, 150, 100, 20);
        l->setJustificationType(juce::Justification::centred);
        addAndMakeVisible(*l);

        labels[p] = std::move(l);
        sliders[p] = std::move(n);
    }

    tsdisplay = std::make_unique<TimeSeriesDisplay>();
    tsdisplay->setBounds(10, 10, getWidth() - 20, 130);
    addAndMakeVisible(*tsdisplay);
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

void AirWinJuceToyAudioProcessorEditor::sliderDragStarted(juce::Slider *s)
{
    sliderDragInternal(s, true);
}

void AirWinJuceToyAudioProcessorEditor::sliderDragEnded(juce::Slider *s)
{
    sliderDragInternal(s, false);
}

void AirWinJuceToyAudioProcessorEditor::sliderDragInternal(juce::Slider *s, bool bv)
{
    for (int p = AirWinJuceToyAudioProcessor::GAIN; p <= AirWinJuceToyAudioProcessor::RESONANCE;
         ++p)
    {
        if (s == sliders[p].get())
        {
            AirWinJuceToyAudioProcessor::UIToAudioMessage msg;
            msg.what = bv ? AirWinJuceToyAudioProcessor::UIToAudioMessage::BEGIN_EDIT
                          : AirWinJuceToyAudioProcessor::UIToAudioMessage::END_EDIT;
            msg.which = (AirWinJuceToyAudioProcessor::Parameters)p;
            processor.uiToAudio.push(msg);
        }
    }
}

void AirWinJuceToyAudioProcessorEditor::sliderValueChanged(juce::Slider *s)
{
    for (int p = AirWinJuceToyAudioProcessor::GAIN; p <= AirWinJuceToyAudioProcessor::RESONANCE;
         ++p)
    {
        if (s == sliders[p].get())
        {
            AirWinJuceToyAudioProcessor::UIToAudioMessage msg;
            msg.what = AirWinJuceToyAudioProcessor::UIToAudioMessage::NEW_VALUE;
            msg.which = (AirWinJuceToyAudioProcessor::Parameters)p;
            msg.newValue = s->getValue();
            processor.uiToAudio.push(msg);
        }
    }
}

void AirWinJuceToyAudioProcessorEditor::idle()
{
    AirWinJuceToyAudioProcessor::AudioToUIMessage msg;
    bool repaintTS{false};
    while (processor.audioToUI.pop(msg))
    {
        switch (msg.what)
        {
        case AirWinJuceToyAudioProcessor::AudioToUIMessage::NEW_VALUE:
            sliders[msg.which]->setValue(msg.newValue,
                                         juce::NotificationType::dontSendNotification);
            break;
        case AirWinJuceToyAudioProcessor::AudioToUIMessage::RMS:
            tsdisplay->push(msg.newValue);
            repaintTS = true;
            break;
        default:
            std::cout << "Unhandled message type " << msg.what << std::endl;
            break;
        }
    }
    if (repaintTS)
        tsdisplay->repaint();
}
