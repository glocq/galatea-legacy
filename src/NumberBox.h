#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <optional>
#include <array>


class NumberBox : public juce::Component
{
public:
    NumberBox(float initialValue);
    NumberBox(int initialValue) : NumberBox((float) initialValue) {}

    void resized() override;

    int getInt();
    float getFloat();

private:
    juce::Colour validColor = findColour(juce::TextEditor::ColourIds::textColourId);
    juce::Colour pendingColor = juce::Colours::grey; // TODO make that depend on global look & feel

    float value;
    juce::TextEditor editor = juce::TextEditor(getName() + " editor", 0);

    static std::optional<float> parseNumber(juce::String);
};
