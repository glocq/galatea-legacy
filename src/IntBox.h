#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <optional>
#include <array>


class IntBoxObserver
{
public:
    virtual void updateValue(int value, juce::String id) = 0;
};

class IntBox : public juce::Component
{
public:
    IntBox(int initialValue, juce::String identifier);

    void resized() override;

    int getValue();

    void addObserver(IntBoxObserver*);
    void removeObserver(IntBoxObserver*);

private:
    juce::Colour validColor = findColour(juce::TextEditor::ColourIds::textColourId);
    juce::Colour pendingColor = juce::Colours::grey; // TODO make that depend on global look & feel

    juce::String id;
    int value;
    juce::TextEditor editor = juce::TextEditor(getName() + " editor", 0);

    // Observer pattern
    std::vector<IntBoxObserver*> observers = {};
    void notifyObservers();

    // Helper function
    static std::optional<int> parseNumber(juce::String);
};

