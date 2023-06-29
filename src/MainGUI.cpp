#include "Processor.h"
#include "MainGUI.h"

//==============================================================================
MainGUI::MainGUI (Processor& p)
    : AudioProcessorEditor(&p)
    , settingsWindow()
    , controlSurface(p.midiSender)
    , processorRef(p)
{
    juce::ignoreUnused(processorRef);

    addAndMakeVisible(settingsButton);
    addAndMakeVisible(controlSurface);

    setResizable(true, true);
    setResizeLimits(500, 500, 10000, 10000);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(700, 700);

    settingsButton.onClick = [&]() { // see https://forum.juce.com/t/open-a-new-window/40347/8
        if(settingsWindow.has_value()) {
            settingsWindow->toFront(true);
        } else {
            settingsWindow.emplace(*this);
            settingsWindow->setVisible(1);
        }
    };
}

MainGUI::~MainGUI()
{
}

//==============================================================================
void MainGUI::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void MainGUI::resized()
{
    int barWidth = 130;
    int barHeight = 30;
    int margin = 10;
    settingsButton.setBounds(margin, margin, barWidth, barHeight);
    controlSurface.setBounds(margin, barHeight + 2 * margin, getWidth() - 2 * margin, getHeight() - 3 * margin - barHeight);
}

void MainGUI::closeSettings()
{
    jassert(settingsWindow.has_value());
    settingsWindow.reset();
}

Processor& MainGUI::getProcessor()
{
    return processorRef;
}
