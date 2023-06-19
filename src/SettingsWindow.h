#pragma once

#include "PluginProcessor.h"


class SettingsWindow : public juce::DocumentWindow
{
public:
    SettingsWindow() : DocumentWindow("Settings", juce::Colours::red, 7, true) {};
};
