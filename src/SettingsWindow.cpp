#include "SettingsWindow.h"
#include "MainGUI.h"


SettingsWindow::SettingsWindow(MainGUI& o) noexcept
    : DocumentWindow(
        "Settings",
        o.getLookAndFeel().findColour(juce::DocumentWindow::backgroundColourId),
        DocumentWindow::closeButton,
        true)
    , owner(o)
    , settings(o.getProcessor().settings)
    , basePitchBox(settings.baseNote, "Base pitch")
    , midiChannelBox(settings.midiChannel, "MIDI channel")
{
    setUsingNativeTitleBar(true);

    centreWithSize(300, 2 * margin + numLines * lineHeight);

    addAndMakeVisible(basePitchLabel);
    addAndMakeVisible(basePitchBox);
    basePitchBox.addObserver(&settings);

    addAndMakeVisible(midiChannelLabel);
    addAndMakeVisible(midiChannelBox);
    midiChannelBox.addObserver(&settings);
}

SettingsWindow::~SettingsWindow()
{
    basePitchBox.removeObserver(&settings);
    midiChannelBox.removeObserver(&settings);
}

void SettingsWindow::closeButtonPressed()
{
    owner.closeSettings();
}

void SettingsWindow::resized()
{
    DocumentWindow::resized();

    auto area = getLocalBounds();
    area.reduce(margin, margin);

    auto firstLine = area.removeFromTop(lineHeight);
    basePitchLabel.setBounds(firstLine.removeFromLeft(100));
    basePitchBox.setBounds(firstLine.removeFromLeft(100));
    auto secondLine = area.removeFromTop(lineHeight);
    midiChannelLabel.setBounds(secondLine.removeFromLeft(100));
    midiChannelBox.setBounds(secondLine.removeFromLeft(100));
}
