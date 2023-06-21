#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class AudioPluginAudioProcessorEditor;


class SettingsWindow : public juce::DocumentWindow
{
public:
    SettingsWindow(AudioPluginAudioProcessorEditor& owner) noexcept;

    void closeButtonPressed() override;

private:
    AudioPluginAudioProcessorEditor& owner;
};
