#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <optional>
#include <array>


class NumberBoxObserver
{
public:
    virtual void updateValue(float value, juce::String id) = 0;
};

class NumberBox : public juce::Component
{
public:
    NumberBox(float initialValue, juce::String identifier);
    NumberBox(int initialValue, juce::String identifier) : NumberBox((float) initialValue, identifier) {}

    void resized() override;

    int getInt();
    float getFloat();

    void addObserver(NumberBoxObserver*);
    void removeObserver(NumberBoxObserver*);

private:
    juce::Colour validColor = findColour(juce::TextEditor::ColourIds::textColourId);
    juce::Colour pendingColor = juce::Colours::grey; // TODO make that depend on global look & feel

    juce::String id;
    float value;
    juce::TextEditor editor = juce::TextEditor(getName() + " editor", 0);

    // Observer pattern
    std::vector<NumberBoxObserver*> observers = {};
    void notifyObservers(float);

    // Helper function
    static std::optional<float> parseNumber(juce::String);
};

