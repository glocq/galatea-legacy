#include "SettingsWindow.h"
#include "PluginEditor.h"


SettingsWindow::SettingsWindow(AudioPluginAudioProcessorEditor& o) noexcept
    : DocumentWindow("Settings", juce::Colours::red, 7, true)
    , owner(o)
{
}

void SettingsWindow::closeButtonPressed()
{
    owner.closeSettings();
}
