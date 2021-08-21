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
    setColour (juce::Slider::thumbColourId, green);
    setColour (juce::Slider::rotarySliderFillColourId, pink);
    setColour (juce::Slider::trackColourId, pink);
    setColour (juce::Slider::backgroundColourId, peach);
    setColour (juce::Slider::rotarySliderOutlineColourId, blue);
    setColour (juce::Label::textColourId, green);
}
