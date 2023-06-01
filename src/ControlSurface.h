#pragma once

#include <JuceHeader.h>

class ControlSurface : public juce::Component
{
public:
    void paint(juce::Graphics& g) override;
    void mouseDown(const MouseEvent&) override;
};

