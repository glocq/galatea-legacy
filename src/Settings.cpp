#include "Settings.h"

#include <juce_core/juce_core.h>
#include <cmath>


void Settings::updateValue(float value, juce::String id)
{
    if (id == "Base pitch") {
        baseNote = (int) std::floor(value);
    } else if (id == "MIDI channel") {
        midiChannel = (int) std::floor(value);
    } else {
        jassert(false);
    }
}
