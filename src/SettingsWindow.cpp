#include "SettingsWindow.h"
#include "PluginEditor.h"


SettingsWindow::SettingsWindow(AudioPluginAudioProcessorEditor& o) noexcept
    : DocumentWindow(
        "Settings",
        o.getLookAndFeel().findColour(juce::DocumentWindow::backgroundColourId),
        7,
        true)
    , owner(o)
{
}

void SettingsWindow::closeButtonPressed()
{
    owner.closeSettings();
}
