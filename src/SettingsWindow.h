#pragma once

#include "PluginEditor.h"


class SettingsWindow : public juce::DocumentWindow
{
public:
    SettingsWindow(PluginEditor& owner);

    closeButtonPressed() override;

private:
    PluginEditor& owner;
};
