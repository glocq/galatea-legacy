#pragma once

#include "NumberBox.h"


class Settings : public NumberBoxObserver
{
public:
    int baseNote = 69; // all noteOn events will be this note, pitch changes will be provided by the pitch wheel
    int midiChannel = 1;

    void updateValue(float value, juce::String id) override;
};
