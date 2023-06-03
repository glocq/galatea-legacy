#pragma once

#include "PluginProcessor.h"
#include "MidiSender.h"
#ifdef LIBINPUT
    #include "PressureDetector.h"
#endif

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

    #ifdef LIBINPUT
        PressureDetector pressureDetector;
    #endif

    // We declare the following just so we don't have to redeclare them every time:
    float x;
    float y;
    float pressure;
};

