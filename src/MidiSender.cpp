#include "MidiSender.h"


MidiSender::MidiSender()
{
}

MidiSender::~MidiSender()
{
}

void MidiSender::registerMouseContact(float xVal, float yVal, float pressureVal)
{
    x = std::max(0.0f, std::min(1.0f, xVal));
    y = std::max(0.0f, std::min(1.0f, yVal));
    pressure = std::max(0.0f, std::min(1.0f, pressureVal));

    pointerDown = true;
    pendingData = true;
}

void MidiSender::registerMouseUp()
{
    pressure = 0;
    pointerDown = false;
    pendingData = true;
}

void MidiSender::getMidiMessages(juce::MidiBuffer& buffer)
{
    if (pendingData) {
        if (pointerDown) {
                buffer.addEvent(juce::MidiMessage::pitchWheel(channel, (int) (16383 * x)), 0);
            if (playing) {
                buffer.addEvent(juce::MidiMessage::channelPressureChange(channel, (int) (pressure * 127)), 0);
            } else {
                buffer.addEvent(juce::MidiMessage::noteOn(channel, baseNote, pressure), 0);
                playing = true;
            }
        } else {
            if (playing) {
                buffer.addEvent(juce::MidiMessage::noteOff(channel, baseNote), 0);
                playing = false;
            }
        }
        pendingData = false;
    }
}
