#include "ControlSurface.h"

ControlSurface::ControlSurface(MidiSender& ms) : midiSenderRef(ms)
{
}

ControlSurface::~ControlSurface()
{
}

void ControlSurface::paint(juce::Graphics& g)
{
    g.fillAll (juce::Colours::darkgrey);
}

void ControlSurface::mouseDown(const juce::MouseEvent& event)
{
    midiSenderRef.registerMouseContact(event, getWidth(), getHeight());
}

void ControlSurface::mouseDrag(const juce::MouseEvent& event)
{
    midiSenderRef.registerMouseContact(event, getWidth(), getHeight());
}

void ControlSurface::mouseUp(const juce::MouseEvent& event)
{
    midiSenderRef.registerMouseUp(event);
}
