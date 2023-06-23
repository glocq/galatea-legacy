#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class MainGUI;


class SettingsWindow : public juce::DocumentWindow
{
public:
    SettingsWindow(MainGUI& owner) noexcept;

    void closeButtonPressed() override;
    void resized() override; // the documentation discourages overriding this, but gives no reason.
                             // it seems that this is ok as long as DocumentWindow::resized() is called inside

private:
    MainGUI& owner;

    juce::Label basePitchLabel {"Base Pitch ", "Base Pitch"};
    juce::TextButton basePitchBtn {"Base MIDI note"};
};
