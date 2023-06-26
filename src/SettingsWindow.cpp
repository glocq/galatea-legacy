#include "SettingsWindow.h"
#include "MainGUI.h"


SettingsWindow::SettingsWindow(MainGUI& o) noexcept
    : DocumentWindow(
        "Settings",
        o.getLookAndFeel().findColour(juce::DocumentWindow::backgroundColourId),
        DocumentWindow::closeButton,
        true)
    , owner(o)
{
    setUsingNativeTitleBar(true);
    centreWithSize(300, 2 * margin + numLines * lineHeight);

    addAndMakeVisible(basePitchLabel);
    addAndMakeVisible(basePitchField);
    basePitchField.setEditable(true);
    addAndMakeVisible(midiChannelLabel);
    addAndMakeVisible(midiChannelField);
    midiChannelField.setEditable(true);
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
    basePitchField.setBounds(firstLine.removeFromLeft(100));
    auto secondLine = area.removeFromTop(lineHeight);
    midiChannelLabel.setBounds(secondLine.removeFromLeft(100));
    midiChannelField.setBounds(secondLine.removeFromLeft(100));

}
