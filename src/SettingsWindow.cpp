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
    centreWithSize(300, 500);
    addAndMakeVisible(basePitchLabel);
    addAndMakeVisible(basePitchBtn);
}

void SettingsWindow::closeButtonPressed()
{
    owner.closeSettings();
}

void SettingsWindow::resized()
{
    DocumentWindow::resized();

    int margin = 30;
    int lineHeight = 30;

    auto area = getLocalBounds();
    area.reduced(margin);

    auto firstLine = area.removeFromTop(lineHeight);
    basePitchLabel.chan
    basePitchLabel.setBounds(firstLine.removeFromLeft(50));
    basePitchBtn.setBounds(firstLine.removeFromLeft(50));

}
