#include "SettingsWindow.h"
#include "MainGUI.h"
#include "Settings.h"


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

    centreWithSize(2*labelWidth, 2 * margin + numLines * lineHeight);

    addAndMakeVisible(basePitchLabel);
    addAndMakeVisible(basePitchBox);
    basePitchBox.addObserver(&settings);

    addAndMakeVisible(midiChannelLabel);
    addAndMakeVisible(midiChannelBox);
    midiChannelBox.addObserver(&settings);

    addAndMakeVisible(coordModeLabel);
    addAndMakeVisible(coordModeMenu);
    coordModeMenu.addItem("Relative", 1);
    coordModeMenu.addItem("Absolute", 2);
    coordModeMenu.onChange = [this] { updateCoordMode(); };
    if (settings.absoluteCoordMode) {
        coordModeMenu.setSelectedId(2);
    } else {
        coordModeMenu.setSelectedId(1);
    }
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
    basePitchLabel.setBounds(firstLine.removeFromLeft(labelWidth));
    basePitchBox.setBounds(firstLine.removeFromLeft(labelWidth));
    auto secondLine = area.removeFromTop(lineHeight);
    midiChannelLabel.setBounds(secondLine.removeFromLeft(labelWidth));
    midiChannelBox.setBounds(secondLine.removeFromLeft(labelWidth));
    auto thirdLine = area.removeFromTop(lineHeight);
    coordModeLabel.setBounds(thirdLine.removeFromLeft(labelWidth));
    coordModeMenu.setBounds(thirdLine.removeFromLeft(labelWidth));
}

void SettingsWindow::updateCoordMode()
{
    switch(coordModeMenu.getSelectedId())
    {
        case 1:
            settings.absoluteCoordMode = false;
            break;
        case 2:
            settings.absoluteCoordMode = true;
            break;
    }
}
