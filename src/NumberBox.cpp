#include "NumberBox.h"

#include <optional>


NumberBox::NumberBox(float initialValue)
{
    value = initialValue;
    editor.setText(juce::String(value));
    addAndMakeVisible(editor);

    editor.onTextChange = [&]() {
        editor.applyColourToAllText(pendingColor);
        editor.repaint();
    };

    editor.onReturnKey = [&]() {
        std::optional<float> v = parseNumber(editor.getText());
        if(v.has_value()) {
            // TODO update listener!!!
            editor.setText(juce::String(v.value()));
            editor.applyColourToAllText(validColor);
        } else {
            editor.applyColourToAllText(pendingColor);
        }
        editor.repaint();
    };
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

std::optional<float> NumberBox::parseNumber(juce::String s)
{
    // Normalize to use dot as a separator between integer and fractional part
    s = s.replaceCharacter(',', '.');

    // Deal with a possible minus sign
    int sign = 1; // is sign positive? (will be changed iff a "-" is encountered)
    if (s.contains("-")) {
        sign = -1;
        // We check that there's nothing apart whitespace before the minus sign
        if (s.upToFirstOccurrenceOf("-", false, false).trim() != "") {
            return {};
        } else {
            // We treat the rest of the number like a regular number
            s = s.fromFirstOccurrenceOf("-", false, false);
        }
    // Maybe the user wanted to make it clear that the number was positive?
    // then we do pretty much the same:
    } else if (s.contains("+")) {
        // We check that there's nothing apart whitespace before the minus sign
        if (s.upToFirstOccurrenceOf("-", false, false).trim() != "") {
            return {};
        } else {
            // We treat the rest of the number like a regular number
            s = s.fromFirstOccurrenceOf("-", false, false);
        }
    }

    s = s.trim(); // remove whitespace around unsigned part

    // Now we can isolate the integer and fractional part...
    juce::String integerPart = s.upToFirstOccurrenceOf(".", false, false);
    juce::String fractionalPart = s.fromFirstOccurrenceOf(".", false, false);
    // check that they are well-formed...
    if (integerPart.containsOnly("0123456789") and fractionalPart.containsOnly("0123456789")) {
        // turn them back into a normalized form...
        s = integerPart + "." + fractionalPart;
        // and parse that
        return(s.getFloatValue() * sign);
    } else {
        return {};
    }
}
