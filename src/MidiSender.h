#pragma once

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_gui_basics/juce_gui_basics.h>


class MidiSender
{
public:
    MidiSender();
    ~MidiSender();
    void registerMouseContact(float x, float y, float pressure);
    void registerMouseUp();
    void getMidiMessages(juce::MidiBuffer&);
    void setX(float);
    void setY(float);
    void setPressure(float);

private:
    bool pointerDown = false;
    bool playing = false; // has a noteOn been sent already?
    bool pendingData = false; // have we received new pointer data since the last time we sent MIDI data?
    float x = 0;
    float y = 0;
    float pressure = 0;
    int channel = 1;
    int baseNote = 60; // all noteOn events will be this note, pitch changes will be provided by the pitch wheel
};

