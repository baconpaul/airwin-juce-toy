//
// Created by Paul Walker on 8/23/21.
//

#ifndef AIRWINDOW_JUCE_TOY_TIMESERIESDISPLAY_H
#define AIRWINDOW_JUCE_TOY_TIMESERIESDISPLAY_H

#include <JuceHeader.h>

struct TimeSeriesDisplay : public juce::Component
{
    void paint(juce::Graphics &g) override;
    static constexpr int n_points = 256; // power of 2 because of dumb hack in push
    std::array<float, n_points> data;
    int wp{0};
    void push(float f)
    {
        data[wp] = f;
        wp = (wp + 1) & (n_points - 1);
    }
};

#endif // AIRWINDOW_JUCE_TOY_TIMESERIESDISPLAY_H
