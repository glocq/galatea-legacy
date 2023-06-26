#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <array>
#include <tuple>

class MainGUI;


class SettingsWindow : public juce::DocumentWindow
{
public:
    enum class InputType {Int, Float, Text};

public:
    SettingsWindow(MainGUI& owner) noexcept;

    void closeButtonPressed() override;
    void resized() override; // the documentation discourages overriding this, but gives no reason.
                             // it seems that this is ok as long as DocumentWindow::resized() is called inside

private:
    MainGUI& owner;

    // Graphical parameters. It's a bit ugly to store them here,
    // I'll find a better solution at some point
    int margin = 20;
    int lineHeight = 20;

    std::array<std::tuple<
        juce::String, // name of the parameter
        juce::String  // current value
    >, 1> parameters = {
        {"MIDI channel", "1"}
    };
};
