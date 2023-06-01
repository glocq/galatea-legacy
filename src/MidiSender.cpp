#include "MidiSender.h"


MidiSender::MidiSender()
{
}

MidiSender::~MidiSender()
{
}

void MidiSender::registerMouseContact(const juce::MouseEvent& event, float componentWidth, float componentHeight)
{
    x = std::max((float) 0, std::min((float) 1, event.position.getX() / componentWidth));
    y = std::max((float) 0, std::min((float) 1, event.position.getY() / componentHeight));
    if (event.isPressureValid()) {
        pressure = event.pressure;
    } else {
        pressure = 1;
    }
    pointerDown = true;
    pendingData = true;
}

void MidiSender::registerMouseUp(const juce::MouseEvent&)
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

void MidiSender::setX(float value)
{
    x = value;
}

void MidiSender::setY(float value)
{
    y = value;
}

void MidiSender::setPressure(float value)
{
    pressure = value;
}

