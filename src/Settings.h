#pragma once

#include "IntBox.h"


class Settings : public IntBoxObserver
{
public:
    int baseNote = 69; // all noteOn events will be this note, pitch changes will be provided by the pitch wheel
    int midiChannel = 1;

    void updateValue(int value, juce::String id) override;
};
