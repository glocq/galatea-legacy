#include "ControlSurface.h"


void ControlSurface::paint(juce::Graphics& g)
{
    g.fillAll (juce::Colours::lightgreen);
}

void ControlSurface::mouseDown(const MouseEvent&)
{
    juce::Logger::writeToLog("Mouse Down!");
}

