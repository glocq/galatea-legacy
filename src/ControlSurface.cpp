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
    mouseContact(event);
}

void ControlSurface::mouseDrag(const juce::MouseEvent& event)
{
    mouseContact(event);
}

void ControlSurface::mouseContact(const juce::MouseEvent& event)
{
    x = event.position.getX() / getWidth();
    y = event.position.getY() / getHeight();

    // If we have libinput, we use our Libinput pressure detector to get the value of pressure;
    // otherwise, we rely on the JUCE mouse event (which, at least on my machine, isn't as reliable)
    #ifdef LIBINPUT
        pressure = pressureDetector.getPressure();
    #else
        if (event.isPressureValid()) {
            pressure = event.pressure;
        } else {
            pressure = 1.;
        }
    #endif

    midiSenderRef.registerMouseContact(x, y, pressure);
}

void ControlSurface::mouseUp(const juce::MouseEvent& /* event */)
{
    midiSenderRef.registerMouseUp();
}
