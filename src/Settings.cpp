#include "Settings.h"

#include <juce_core/juce_core.h>
#include <cmath>


void Settings::updateValue(int value, juce::String id)
{
    if (id == "Base pitch") {
        baseNote = value;
    } else if (id == "MIDI channel") {
        midiChannel = value;
    } else {
        jassert(false);
    }
}
