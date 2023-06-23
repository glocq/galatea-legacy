#pragma once

#include "Processor.h"
#include "SettingsWindow.h"
#include "ControlSurface.h"

//==============================================================================
class MainGUI : public juce::AudioProcessorEditor
{
public:
    explicit MainGUI(Processor&);
    ~MainGUI() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    //==============================================================================
    void closeSettings();

private:
    juce::TextButton settingsButton {"Surface settings"};
    std::optional<SettingsWindow> settingsWindow;
    ControlSurface controlSurface;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Processor& processorRef;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainGUI)
};
