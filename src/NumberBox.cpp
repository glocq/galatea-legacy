#include "NumberBox.h"


NumberBox::NumberBox(float initialValue)
{
    value = initialValue;
    editor.setText(juce::String(value));
    addAndMakeVisible(editor);
}

NumberBox::NumberBox(int initialValue)
{
    value = (float) initialValue;
    editor.setText(juce::String(value));
    addAndMakeVisible(editor);
}

void NumberBox::resized()
{
    editor.setBounds(getLocalBounds());
}

int NumberBox::getInt()
{
    return (int) value;
}

float NumberBox::getFloat()
{
    return value;
}
