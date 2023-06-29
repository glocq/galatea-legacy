#pragma once

#include <juce_gui_basics/juce_gui_basics.h>


class NumberBox : public juce::Component
{
public:
    NumberBox(float initialValue);
    NumberBox(int initialValue);

    void resized() override;

    int getInt();
    float getFloat();

private:
    float value;
    juce::TextEditor editor = juce::TextEditor(getName() + " editor", 0);
};
