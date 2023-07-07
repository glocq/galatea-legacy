#include "IntBox.h"

#include <algorithm>


IntBox::IntBox(int initialValue, juce::String str)
{
    id = str;

    value = initialValue;
    editor.setText(juce::String(value));

    addAndMakeVisible(editor);

    editor.onTextChange = [&]() {
        editor.applyColourToAllText(pendingColor);
        editor.repaint();
    };

    editor.onReturnKey = [&]() {
        std::optional<int> v = parseNumber(editor.getText());
        if(v.has_value()) {
            value = v.value();
            notifyObservers();
            editor.setText(juce::String(value));
            editor.applyColourToAllText(validColor);
        } else {
            editor.applyColourToAllText(pendingColor);
        }
        editor.repaint();
    };
}

void IntBox::resized()
{
    editor.setBounds(getLocalBounds());
}

int IntBox::getValue()
{
    return value;
}

void IntBox::addObserver(IntBoxObserver* new_observer)
{
    observers.push_back(new_observer);
}

void IntBox::removeObserver(IntBoxObserver* obs)
{
    auto position = std::find(observers.begin(), observers.end(), obs);
    jassert(position != observers.end());
    observers.erase(position);
}

void IntBox::notifyObservers()
{
    for(IntBoxObserver* obs : observers) {
        obs->updateValue(value, id);
    }
}

/**
 * This function parses an integer number, but will accept floating values,
 * it will simply round the value down to the integer below (or above, if below zero)
 * This decision is debatable, but in any case it makes it easy to adapt
 * to the floating point case.
 */
std::optional<int> IntBox::parseNumber(juce::String s)
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
    // (the fractional part bit is useless, but makes it easy to adapt
    // to the floating point case)
    juce::String integerPart = s.upToFirstOccurrenceOf(".", false, false);
    juce::String fractionalPart = s.fromFirstOccurrenceOf(".", false, false);
    // check that they are well-formed...
    if (integerPart.containsOnly("0123456789") and fractionalPart.containsOnly("0123456789")) {
        // turn them back into a normalized form...
        s = integerPart + "." + fractionalPart;
        // and parse that
        return(std::make_optional<int>(integerPart.getFloatValue() * sign));
    } else {
        return {};
    }
}
