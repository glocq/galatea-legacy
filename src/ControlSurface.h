#pragma once

#include "PluginProcessor.h"
#include "MidiSender.h"


class ControlSurface : public juce::Component
{
public:
    ControlSurface(MidiSender&);
    ~ControlSurface();

    void paint(juce::Graphics& g) override;

    // Mouse listening
    void mouseDown(const juce::MouseEvent&) override;
    void mouseDrag(const juce::MouseEvent&) override;
    void mouseUp(const juce::MouseEvent&) override;

private:
    void mouseContact(const juce::MouseEvent&);
    MidiSender& midiSenderRef;
};

