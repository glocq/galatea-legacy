#include "ControlSurface.h"

#include <juce_gui_basics/juce_gui_basics.h>


ControlSurface::ControlSurface(MidiSender& ms) : midiSenderRef(ms)
                                            #ifdef LIBINPUT
                                               , libinputManager(*this)
                                            #endif
{
    // We assume we're using the primary display. TODO choose the right display (no idea how to do that...)

    const juce::Displays::Display* display = juce::Desktop::getInstance().getDisplays().getPrimaryDisplay();
    if(display) {
        screenWidth = display->totalArea.getWidth();
        screenHeight = display->totalArea.getHeight();
    } else {
        juce::Logger::outputDebugString("Failed to get screen dimensions, using 1000x1000 instead");
    }
}

void ControlSurface::paint(juce::Graphics& g)
{
    g.fillAll (juce::Colours::darkgrey);
}


#ifndef LIBINPUT

void ControlSurface::mouseDown(const juce::MouseEvent& event)
{
    x = ((float) event.getScreenX()) / ((float) screenWidth);
    y = ((float) event.getScreenY()) / ((float) screenHeight);

    if (event.isPressureValid()) {
        pressure = event.pressure;
    } else {
        pressure = 1;
    }

    midiSenderRef.registerMouseContact(x, y, pressure);
}

void ControlSurface::mouseDrag(const juce::MouseEvent& event)
{
    x = ((float) event.getScreenX()) / ((float) screenWidth);
    y = ((float) event.getScreenY()) / ((float) screenHeight);

    if (event.isPressureValid()) {
        pressure = event.pressure;
    } else {
        pressure = 1;
    }

    midiSenderRef.registerMouseContact(x, y, pressure);
}


void ControlSurface::mouseUp(const juce::MouseEvent& /* event */)
{
    midiSenderRef.registerMouseUp();
}

#else

void ControlSurface::libinputContact(float xVal, float yVal, float pressureVal)
{
    midiSenderRef.registerMouseContact(xVal, yVal, pressureVal);
}

void ControlSurface::libinputRelease()
{
    midiSenderRef.registerMouseUp();
}

#endif
