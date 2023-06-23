#pragma once

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_gui_basics/juce_gui_basics.h>

#include "Settings.h"


class MidiSender
{
public:
    MidiSender(Settings&);
    ~MidiSender();
    void registerMouseContact(float x, float y, float pressure);
    void registerMouseUp();
    void getMidiMessages(juce::MidiBuffer&);

private:
    bool pointerDown = false;
    bool playing = false; // has a noteOn been sent already?
    bool pendingData = false; // have we received new pointer data since the last time we sent MIDI data?
    float x = 0;
    float y = 0;
    float pressure = 0;

    Settings& settings;
};

