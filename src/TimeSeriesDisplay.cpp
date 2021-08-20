//
// Created by Paul Walker on 8/23/21.
//

#include "TimeSeriesDisplay.h"

void TimeSeriesDisplay::paint(juce::Graphics &g)
{
    g.fillAll(juce::Colours::lightgrey);

    float dx = getWidth() * 1.f / n_points;

    g.setColour(juce::Colours::blue);
    for (int i = 0; i < n_points; ++i)
    {
        // not very efficient
        auto h = 2.f * data[i] * getHeight();
        g.fillRect(i * dx, getHeight() - h, dx, h);
    }
    g.setColour(juce::Colours::red);
    g.fillRect(wp * dx, 0.f, 1.f, 1.f * getHeight());
}