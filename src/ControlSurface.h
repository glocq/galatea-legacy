#pragma once

#include "PluginProcessor.h"
#include "MidiSender.h"

#ifdef LIBINPUT
    #include "LibinputManager.h"
#endif


class ControlSurface : public juce::Component
{
public:

    ControlSurface(MidiSender&);

    void paint(juce::Graphics& g) override;

    // Mouse/stylus listening
    #ifndef LIBINPUT
        void mouseDown(const juce::MouseEvent&) override;
        void mouseDrag(const juce::MouseEvent&) override;
        void mouseUp(const juce::MouseEvent&) override;
    #else
        void libinputContact(float x, float y, float pressure);
        void libinputRelease();
    #endif

private:
    MidiSender& midiSenderRef;

    #ifdef LIBINPUT
        LibinputManager libinputManager;
    #endif

    // We need those if in absolute coordinates.
    int screenWidth = 1000;
    int screenHeight = 1000;

    // We declare the following just so we don't have to redeclare them every time:
    float x;
    float y;
    float pressure;
};
