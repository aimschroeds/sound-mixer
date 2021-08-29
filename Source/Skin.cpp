/*
  ==============================================================================

    Skin.cpp
    Created: 21 Aug 2021 3:40:00pm
    Author:  Aimee Schroeder

  ==============================================================================
*/

#include "Skin.h"

Skin::Skin()
{
    setColour (juce::Slider::thumbColourId, blue);
    setColour (juce::Slider::rotarySliderFillColourId, pink);
    setColour (juce::Slider::trackColourId, pink);
    setColour (juce::Slider::backgroundColourId, peach);
    setColour (juce::Slider::rotarySliderOutlineColourId, blue);
    setColour (juce::Label::textColourId, green);
    setColour (juce::TextButton::buttonColourId, green);
    setColour (juce::TextButton::textColourOffId, juce::Colours::ghostwhite);
    setColour (juce::TextEditor::backgroundColourId, juce::Colours::ghostwhite);
    setColour (juce::TextEditor::textColourId, black);
    setColour (juce::TextEditor::focusedOutlineColourId, blue);
    setColour (juce::TextEditor::outlineColourId, peach);
}
