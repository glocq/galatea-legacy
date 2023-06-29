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
    , basePitchBox(settings.baseNote)
{
    setUsingNativeTitleBar(true);

    centreWithSize(300, 2 * margin + numLines * lineHeight);

    addAndMakeVisible(basePitchLabel);
    addAndMakeVisible(basePitchBox);
    addAndMakeVisible(midiChannelLabel);
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

}
