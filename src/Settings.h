#pragma once


class Settings
{
public:
    int baseNote = 69; // all noteOn events will be this note, pitch changes will be provided by the pitch wheel
    int midiChannel = 1;
};
