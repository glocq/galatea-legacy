#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <array>
#include <tuple>

#include "Settings.h"
#include "NumberBox.h"

class MainGUI;


class SettingsWindow : public juce::DocumentWindow
{
public:
    enum class InputType {Int, Float, Text};

public:
    SettingsWindow(MainGUI&) noexcept;
    ~SettingsWindow() override;

    void closeButtonPressed() override;
    void resized() override; // the documentation discourages overriding this, but gives no reason.
                             // it seems that this is ok as long as DocumentWindow::resized() is called inside

private:
    MainGUI& owner;
    Settings& settings;

    // Graphical parameters. It's a bit ugly to store them here,
    // I'll find a better solution at some point
    int margin = 20;
    int lineHeight = 20;
    int numLines = 1;

    juce::Label basePitchLabel = juce::Label("Base pitch label", "Base Pitch");
    NumberBox basePitchBox;
    juce::Label midiChannelLabel = juce::Label("MIDI channel label", "MIDI channel");
    NumberBox midiChannelBox;
};
